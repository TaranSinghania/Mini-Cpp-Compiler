from optim import *
dead_code_elimination()
print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))
# i = 0
# j = 0
# flag = 1
# dont_remove = 0

# while (flag == 1):
# 	flag = 0
# 	i = 0
# 	while (i < len(lines)):
# 		dont_remove = 0
# 		if not ((lines[i][0] == 'call') or (lines[i][0] == 'Label') or (lines[i][0] == 'goto') or (lines[i][0] == 'IfFalse')):
# 			j = 0
# 			while (j < len(lines)):
# 				if (lines[i][3] == lines[j][1]) or (lines[i][3] == lines[j][2]) or (lines[j][0] == 'param' and lines[j][3] == lines[i][3]):
# 					dont_remove = 1
# 				j = j + 1

# 			if (dont_remove == 0):
# 				del lines[i]
# 				flag = 1
# 				i = i - 1


# 		i = i + 1

