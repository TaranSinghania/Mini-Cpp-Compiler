from optim import *
common_subexpression_elimination()
print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))