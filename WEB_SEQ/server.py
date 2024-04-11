from flask import Flask, render_template, request, redirect, url_for
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/alignment', methods=['POST'])
def get_alignment():
    try:
        # Get input parameters from the form
        input_file_1 = request.files['input_file_1']
        input_file_2 = request.files['input_file_2']
        match = request.form.get('match', default=3, type=int)
        mismatch = request.form.get('mismatch', default=-1, type=int)
        gap = request.form.get('gap', default=-2, type=int)
        
        # Save the uploaded files
        input_file_1.save(input_file_1.filename)
        input_file_2.save(input_file_2.filename)

        # Convert integers to strings
        match_str = str(match)
        mismatch_str = str(mismatch)
        gap_str = str(gap)

        # Execute the C++ program with the input parameters
        result = subprocess.run(['/app/cpp/alignment/alignment', input_file_1.filename, input_file_2.filename, match_str, mismatch_str, gap_str], capture_output=True, text=True)

        if result.returncode == 0:
            return render_template('result.html', output=result.stdout)
        else:
            return render_template('result.html', error=result.stderr)

    except Exception as e:
        return render_template('result.html', error=str(e))

@app.route('/horspool', methods=['POST'])
def get_horspool():
    try:
        # Get input parameters from the form
        input_file = request.files['input_file']
        pattern = request.form['pattern']

        # Save the uploaded file
        input_file.save(input_file.filename)

        # Execute the C++ program with the input parameters
        result = subprocess.run(['/app/cpp/horspool/hpf', input_file.filename, pattern], capture_output=True, text=True)

        if result.returncode == 0:
            return render_template('result.html', output=result.stdout)
        else:
            return render_template('result.html', error=result.stderr)

    except Exception as e:
        return render_template('result.html', error=str(e))

@app.route('/ahoc', methods=['POST'])
def get_trie():
    try:
        text_file = request.files['text_file']
        patterns = request.form.getlist('pattern')

        # Save the uploaded text file
        text_file.save(text_file.filename)

        # Execute the C++ program with the input parameters
        result = subprocess.run(['/app/cpp/aho/ahoc', text_file.filename] + patterns, capture_output=True, text=True)

        if result.returncode == 0:
            return render_template('result.html', output=result.stdout)
        else:
            return render_template('result.html', error=result.stderr)

    except Exception as e:
        return render_template('result.html', error=str(e))

@app.route('/qgi', methods=['POST'])
def search_qgi():
    try:
        genome_file = request.files['genome_file']
        query = request.form['query']

        # Save the uploaded genome file
        genome_file.save(genome_file.filename)

        # Execute the C++ program with the input parameters
        result = subprocess.run(['/app/cpp/qgi/qgi', genome_file.filename, query], capture_output=True, text=True)

        if result.returncode == 0:
            return render_template('result.html', output=result.stdout)
        else:
            return render_template('result.html', error=result.stderr)

    except Exception as e:
        return render_template('result.html', error=str(e))


@app.route('/blast', methods=['POST'])
def search_blast():
    try:
        seq = request.form['seq']
        score_matrix = request.form.get('score_matrix')
        word_size = request.form.get('word_size', type=int)
        score_threshold = request.form.get('score_threshold', type=int)
      
        result = subprocess.run(['/app/cpp/blast/blast', seq, score_matrix, str(word_size), str(score_threshold)], capture_output=True, text=True)

        if result.returncode == 0:
            return render_template('result.html', output=result.stdout)
        else:
            return render_template('result.html', error=result.stderr)

    except Exception as e:
        return render_template('result.html', error=str(e))


class RNASequence:
    def __init__(self, rna):
        self.rna = rna
        self.N = len(rna)
        self.score = [[0] * self.N for _ in range(self.N)]
        self.structure = ['.'] * self.N

    def calculate_structure(self):
        self.fill_score_matrix()
        self.traceback(0, self.N - 1)
        return ''.join(self.structure)

    def fill_score_matrix(self):
        for k in range(1, self.N):
            for i in range(self.N - k):
                j = i + k
                if j - i >= 4:  # Min loop length
                    match = (self.rna[i] == 'A' and self.rna[j] == 'U') or \
                            (self.rna[i] == 'U' and self.rna[j] == 'A') or \
                            (self.rna[i] == 'G' and self.rna[j] == 'C') or \
                            (self.rna[i] == 'C' and self.rna[j] == 'G') or \
                            (self.rna[i] == 'G' and self.rna[j] == 'U') or \
                            (self.rna[i] == 'U' and self.rna[j] == 'G')

                    self.score[i][j] = max(max(self.score[i + 1][j], self.score[i][j - 1]),
                                            self.score[i + 1][j - 1] + match)

                    for t in range(i + 1, j):
                        self.score[i][j] = max(self.score[i][j], self.score[i][t] + self.score[t + 1][j])

    def traceback(self, i, j):
        stack = [(i, j)]

        while stack:
            i, j = stack.pop()

            if j - i >= 4:
                if self.score[i][j] == self.score[i + 1][j]:
                    stack.append((i + 1, j))
                elif self.score[i][j] == self.score[i][j - 1]:
                    stack.append((i, j - 1))
                elif self.score[i][j] == self.score[i + 1][j - 1] + \
                                          ((self.rna[i] == 'A' and self.rna[j] == 'U') or
                                           (self.rna[i] == 'U' and self.rna[j] == 'A') or
                                           (self.rna[i] == 'G' and self.rna[j] == 'C') or
                                           (self.rna[i] == 'C' and self.rna[j] == 'G') or
                                           (self.rna[i] == 'G' and self.rna[j] == 'U') or
                                           (self.rna[i] == 'U' and self.rna[j] == 'G')):
                    self.structure[i] = '('
                    self.structure[j] = ')'
                    stack.append((i + 1, j - 1))
                else:
                    for t in range(i + 1, j):
                        if self.score[i][j] == self.score[i][t] + self.score[t + 1][j]:
                            stack.append((i, t))
                            stack.append((t + 1, j))
                            break

@app.route('/rna', methods=['GET', 'POST'])
def rna():
    if request.method == 'POST':
        rna_sequence = request.form['rna_sequence']
        nussinov = RNASequence(rna_sequence)
        structure = nussinov.calculate_structure()
        return render_template('result.html', output=structure)
    return render_template('index.html')




if __name__ == '__main__':
    app.run(debug=True)
