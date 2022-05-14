import os

testcase_num = 11

folderName = input ()
testcase_num = int(input ())

os.system("./compile.sh")

for i in range(1, testcase_num + 1):
    print("processing", i, "...")
    # os.system("rm *.dat")
    # os.system("rm log.txt")
    os.system("./code < total_rollback/" + folderName + "/" + str(i) + ".in > force/" + str(i) + ".out")

# for i in range(1, testcase_num + 1):
#     print("evaluate", i, "...")
#     ret = os.system("diff test/{}.out bin/naive_{}.out".format(i, i))
#     if ret != 0:
#         print("error in", i, "!")