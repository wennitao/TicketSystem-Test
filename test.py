import os

testcase_num = 11

folderName = input ()
testcase_num = int(input ())

os.system("./compile.sh")
os.system("rm *.dat")
os.system("rm log.txt")

for i in range(1, testcase_num + 1):
    print("processing", i, "...")
    os.system("./code < total_rollback/" + folderName + "/" + str(i) + ".in > force/" + folderName + "/" + str(i) + ".out")

os.system("rm *.dat")
os.system("rm log.txt")
for i in range(1, testcase_num + 1):
    print("processing", i, "...")
    os.system("./rollback < total_rollback/" + folderName + "/" + str(i) + ".in > test/" + folderName + "/" + str(i) + ".out")

for i in range(1, testcase_num + 1):
    print("evaluate", i, "...")
    ret = os.system("diff force/{}.out test/{}.out".format(i, i))
    if ret != 0:
        print("error in", i, "!")