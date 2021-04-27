from sys import stdin
import re

lines=[]

is_int=lambda x: bool(re.match("(-)?[0-9]+", x))

is_float=lambda x: bool(re.match("(-)?[0-9]+\.[0-9]+", x))

is_variable= lambda x: bool(re.match("[a-zA-Z_][a-zA-Z0-9_]*", x))

is_str= lambda x: bool(re.match("(\".*\")|(\'.*\')", x))

is_bool = lambda x: x=="True" or x=="False"

is_const = lambda x: is_int(x) or is_bool(x) or is_float(x) or is_str(x)

operators={'+','-','*','/','//','%','in','and','or','|','&','**','^','not','>>','<<',"==","!=",">","<",">=","<="}

for line in stdin:
    if line.split(" ")[0] != "Expression": 
        temp=line.strip().split("\t")
        if temp!=['']:
            lines.append(temp)
#print(lines)

def constant_folding():
    changed=0
    for i in range(len(lines)):
        if lines[i][0] in operators:
            if is_const(lines[i][1]) and is_const(lines[i][2]):
                ans=eval(lines[i][1]+lines[i][0]+lines[i][2])
                changed=1
                lines[i][0]="="
                lines[i][1]=str(ans)
                lines[i][2]=" "
    
    return changed

def constant_propagation():
    d={}
    changed=0
    for i in range(len(lines)):
        try:
            if lines[i][0]=='=' and is_const(lines[i][1]) :
                d[lines[i][-1]]=lines[i][1]
                continue
        except:
            pass
        try:
            if is_variable(lines[i][1]):
                if lines[i][1] in d:
                    changed=1
                    lines[i][1]=d[lines[i][1]]
        except:
            pass
        try:
            if is_variable(lines[i][2]):
                if lines[i][2] in d:
                    changed=1
                    lines[i][2]=d[lines[i][2]]
        except:
            pass

    return changed


def copy_propagation():
    d={}
    changed=0
    for i in range(len(lines)):
        if lines[i][0]=='=' and is_variable(lines[i][1]) and lines[i][2]==' ' :
            d[lines[i][-1]]=lines[i][1]
            continue

        if is_variable(lines[i][1]):
            if lines[i][1] in d:
                changed=1
                lines[i][1]=d[lines[i][1]]
        try:
            if is_variable(lines[i][2]):
                if lines[i][2] in d:
                    changed=1
                    lines[i][2]=d[lines[i][2]]
        except:
            pass
    return changed


def dead_code_elimination():
    flag=None
    i=0
    while i<len(lines):
        try:
            if lines[i][3] == flag:
                del lines[i]
                flag=None
        except:
            pass

        if((lines[i][0] == 'if' and lines[i][1]=='False') or (lines[i][0] == 'ifFalse' and lines[i][1]=='True')):
            while lines[i][0] != 'Label':
                del lines[i]
            del lines[i]

        if((lines[i][0] == 'if' and lines[i][1]=='True') or (lines[i][0] == 'ifFalse' and lines[i][1]=='False')):
            flag=lines[i][3]
            del lines[i]
            
        i=i+1

    for i in range(len(lines)):
        for j in range(i+1,len(lines)):
            if j>=len(lines):
                break
            try:
                if(lines[j][0] == 'Label' and lines[j][3] == flag):
                    flag=None
            except:
                pass
            if flag!=None:
                continue
            if(lines[j][0] == 'if' or lines[j][0] == 'ifFalse'):
                flag=lines[j][3]
            if(lines[i][3] == lines[j][1]):
                break
            try:
                if(lines[i][0]=="=" and lines[j][0]=="=" and lines[i][3] == lines[j][3]):
                    del lines[i]
            except:
                pass
    i = len(lines)-1
    while i >= 0:
        flag = 0

        if lines[i][0] == 'param' or lines[i][0] == 'call' or lines[i][0] == 'Label' or lines[i][0] == 'IfFalse' or lines[i][0] == 'if' or lines[i][0] == 'goto':
            i-=1
            continue
        for j in range(i+1,len(lines)):
            try:
                if(lines[i][3] == lines[j][1]):
                    flag += 1
                elif lines[j][0] == 'param' and lines[j][3] == lines[i][3]:
                    flag += 1
            except:
                pass
        if flag == 0 :
            del lines[i]
        i-=1

    return 1

def replaceAll(CSE, replaceStr, CSE_len, start_index):
    i = 0
    while (i < CSE_len):
        j = start_index
        while (j < len(lines)):
            if (lines[j][1] == CSE[i]):
                lines[j][1] = replaceStr
            if (lines[j][2] == CSE[i]):
                lines[j][2] = replaceStr
            j = j + 1
        i = i + 1

def common_subexpression_elimination():
    i = 0
    changed = 0
    while (i < len(lines)):
        temp = lines[i]
        CSEs = dict()
        CSE_index = 0
        j = i + 1
        while (j < len(lines)):
            if (lines[j][0] == temp[0]) and (lines[j][1] == temp[1]) and (lines[j][2] == temp[2]) and (temp[0] != 'print') and (temp[0] != 'call') and (temp[0] != 'param') and (temp[0] != 'Label') and (temp[0] != '='):
                CSEs[CSE_index] = lines[j][3]
                # print(temp, lines[j])
                # print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))
                # print("----------")
                del lines[j]
                changed = 1
                CSE_index += 1

            if (CSE_index > 0):
                try:
                    replaceAll(CSEs, temp[3], CSE_index, j)
                except:
                    pass
            j = j + 1

        i = i + 1
        # print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))


# changed=1
# while changed:
#     c1=constant_folding()
#     c2=constant_propagation()
#     c3=copy_propagation()
#     c4=common_subexpression_elimination()
#     changed=c1 or c2 or c3 or c4
#     #break


# # common_subexpression_elimination()
# # print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))
# # print("--------")
# dead_code_elimination()

# changed=1 #after dead_code_elimination, we can still do some constant folding, propagation because, some loop blocks like elif and else can sometimes be eliminated. So can evaluate the expressions, propagate contstants,etc
# while changed:
#     c1=constant_folding()
#     c2=constant_propagation()
#     c3=copy_propagation()
#     c4=common_subexpression_elimination()
#     changed=c1 or c2 or c3 or c4

# common_subexpression_elimination()

# print('\n'.join(list(map(lambda line:'\t'.join(line),lines))))
