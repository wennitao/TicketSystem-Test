import os

testcase_num = 11

os.system("./compile.sh")

for i in range(testcase_num):
    print("processing", i, "...")
    os.system("rm *.dat")
    os.system("./code < bin/" + str(i) + ".in > test/" + str(i) + ".out")

for i in range(testcase_num):
    print("evaluate", i, "...")
    ret = os.system("diff test/{}.out bin/naive_{}.out".format(i, i))
    if ret != 0:
        print("error in", i, "!")