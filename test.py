import os
import time

testcase_num = 11

folderName = input ()
testcase_num = int(input ())

def runForce():
    os.system("rm *.dat")
    os.system("rm log.txt")
    for i in range(1, testcase_num + 1):
        print("brute-force", i, "...")
        os.system("./code < total_rollback/" + folderName + "/" + str(i) + ".in > force/" + str(i) + ".out")

def runRollback():
    os.system("./compile.sh")
    os.system("rm *.dat")
    os.system("rm log.txt")
    os.system("mkdir test/" + folderName)
    t = time.time()
    for i in range(1, testcase_num + 1):
        print("rollback", i, "...")
        os.system("touch test/" + folderName + "/" + str(i) + ".out")
        curCaseT = time.time()
        os.system("./rollback < total_rollback/" + folderName + "/" + str(i) + ".in > test/" + folderName + "/" + str(i) + ".out")
        curT = time.time() - curCaseT
        print(str(i) + ".in " + str(curT) + " seconds")
    tt = time.time() - t
    print("total time: " + str(tt) + " seconds")

def runEvaluate():
    for i in range(1, testcase_num + 1):
        print("evaluate", i, "...")
        ret = os.system("diff test/" + folderName + "/" + str(i) + ".out" + " out/" + folderName + "/" + str(i) + ".out")
        if ret != 0:
            print("error in", i, "!")

# runForce()
runRollback()
runEvaluate()