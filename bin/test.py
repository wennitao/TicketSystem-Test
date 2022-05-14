import os

testcase_num = 11

def build(naive):
    if naive:
        prefix = "naive_"
    else:
        prefix = "rollback_"
    os.system("touch a.dat")
    for i in range(testcase_num):
        print("processing", i, "...")
        os.system("../cmake-build-debug/code < " + str(i) + ".in > " + prefix + str(i) + ".out")
    os.system("rm *.dat")

def eval():
    for i in range(testcase_num):
        print("evaluate", i, "...")
        ret = os.system("diff naive_{}.out rollback_{}.out".format(i, i))
        if ret != 0:
            print("error in", i, "!")
            # exit(1)


if __name__ == '__main__':
    # build(False)
    eval()