import re

class LexicalAnalyzer:
  """A simple lexical analyzer for arithmetic expressions.
  """

  # Mapping from math lexemes to tokens.
  tokens_ = {'+': 'PLUS', '-': 'MINUS', '*': 'STAR',
             '/': 'SLASH', '(': 'LPAR', ')': 'RPAR', '^': 'CARRET'}

  def __init__(self, input):
    """Constructor, splits the input string into lexemes, 
       and calls lex() for the first time.
    """
    self.lexemes_ = []
    self.pos_ = 0

    p = re.compile(r"[-+*/()^]");
    chunks = input.split()
    for chunk in chunks:
      m = p.search(chunk)
      while m:
        if m.start() > 0:
          self.lexemes_.append(chunk[:m.start()])
        self.lexemes_.append(m.group())
        chunk = chunk[m.end():]
        m = p.search(chunk)
      if chunk:
        self.lexemes_.append(chunk)

    self.lex()
      

  def lex(self):
    """Sets the nextLexeme_ attribute to the next lexeme,
       and computes the corresponding token in nextToken_.
    """
    if self.pos_ == len(self.lexemes_):
      self.nextToken_ = 'EOF'
      self.nextLexeme_ = ''
      return

    self.nextLexeme_ = self.lexemes_[self.pos_]
    self.pos_ += 1

    try:
      self.nextToken_ = self.tokens_[self.nextLexeme_]
    except KeyError:
      if self.nextLexeme_.isdigit():
        self.nextToken_ = 'NUMBER'
      else:
        self.nextToken_ = 'UNKNOWN'
