import os
import sys

# Parameter: Time (ms)
time_limit_cpp = 1000
time_limit_python = 3000

# Parameter: Memory (MB)
memory_limit_cpp = 1000
memory_limit_python = 1000

source_files = os.listdir('source')
input_files = os.listdir('input')
output_files = os.listdir('output')

pair = {}

for i in input_files:
    for j in output_files:
        if i[:i.find('.')] == j[:j.find('.')]:
            pair[i] = j

os.system("gcc -o judge judge.c")
os.system("ls input/* > files")

# ----- if need special judge -----
# os.system("g++ -o spj spj.cpp")
# ---------------------------------

for source in source_files:
    name = source[:source.find('.')]
    lang = source[source.find('.') + 1:]

    os.mkdir('result/{}'.format(name))

    if lang == 'cpp':
        ret = os.system("g++ -O2 -o {} source/{}".format(name, source))
        if ret:
            outstr = '{}: Compile Error\n'.format(name)
            f = open("result/{}_out.txt".format(name), "wt")
            f.write(outstr)
            f.close()
            continue
        else:
            os.system("./judge ./{} files {} {} {} > out".format(name, lang, time_limit_cpp, memory_limit_cpp))
            os.system("rm {}".format(name))
    elif lang == 'py':
        os.system("./judge {} files {} {} {} > out".format(name, lang, time_limit_python, memory_limit_python))
    else:
        continue

    outstr = ''
    ac = 0
    total = 0

    f = open("out", "rt")
    while True:
        arr = f.readline().split()
        if not arr:
            break
        total += 1
        i = arr[0][6:]
        if arr[1] == '0':
# ---------- normal form ---------
            out = os.system("diff -bZ output/{} result/{}/{}_out".format(pair[i], name, i))
# --------------------------------

# ----- if need special judge -----
# out = os.system("./spj input/{} result/{}/{}_out".format(i, source, i))
# ---------------------------------
            if out != 0:
                outstr += "{}: Wrong Answer\n".format(i)
            else:
                outstr += "{}: Accepted (Time: {}ms, Memory: {}KB)\n".format(i, arr[2], arr[3])
                ac += 1
        elif arr[1] == '1':
            outstr += "{}: Runtime Error\n".format(i)
            outstr += "Information: "
            for line in range(int(arr[2])):
                outstr += f.readline()
        elif arr[1] == '2':
            outstr += "{}: Time Limit Exceeded\n".format(i)
        elif arr[1] == '3':
            outstr += "{}: Memory Limit Exceeded\n".format(i)

    f.close()

    os.system("rm err")
    os.system("rm out")

    outstr = "{}: {}/{}\n".format(name, ac, total) + outstr
    f = open("result/{}_out.txt".format(name), "wt")
    f.write(outstr)
    f.close()

os.system("rm judge")
os.system("rm files")

# ----- if need special judge -----
# os.system("rm spj")
# ---------------------------------
