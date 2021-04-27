from optim import *
copy_propagation()
print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))