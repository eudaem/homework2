import os
os.system("g++ core.cpp -O2 && ./a.out")
print("compile and generate done.")
for i in range(0,100):
    os.system("pypy test%d.py" % i)
    print("test%d done." % i)