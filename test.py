import os

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
    for i in range(1, testcase_num + 1):
        print("rollback", i, "...")
        os.system("./rollback < total_rollback/" + folderName + "/" + str(i) + ".in > test/" + str(i) + ".out")

def runEvaluate():
    for i in range(1, testcase_num + 1):
        print("evaluate", i, "...")
        ret = os.system("diff force/{}.out test/{}.out".format(i, i))
        if ret != 0:
            print("error in", i, "!")

runForce()
runRollback()
runEvaluate()