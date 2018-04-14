import os
import time
os.system("g++ core.cpp -O2 -g")
print("compile done.")
time.sleep(1);
os.system("./a.out")
time.sleep(1);
print("generate done.")
for i in range(0,100):
    os.system("pypy test%d.py" % i)
    print("test%d done." % i)