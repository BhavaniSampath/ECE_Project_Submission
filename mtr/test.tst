# TestMtr Version #0.6, Release date 2/6/12
# mtr/testmtr -p 2 ./mtr/test.groups
N=0x563e4a86a2b0 C=0x563e4a86a370 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=0
N=0x563e4a86a370 C=0x0        Y=0x563e4a86a3b0 E=0x0        P=0x563e4a86a2b0 F=3 L=0 S=0
N=0x563e4a86a3b0 C=0x0        Y=0x563e4a86a2f0 E=0x563e4a86a370 P=0x563e4a86a2b0 F=4 L=0 S=0
N=0x563e4a86a2f0 C=0x0        Y=0x563e4a86a330 E=0x563e4a86a3b0 P=0x563e4a86a2b0 F=1 L=0 S=0
N=0x563e4a86a330 C=0x0        Y=0x0        E=0x563e4a86a2f0 P=0x563e4a86a2b0 F=2 L=0 S=0
#------------------------
N=0x563e4a86a2b0 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
#  (0,11)

N=0x563e4a86a2b0 C=0x563e4a86a370 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x563e4a86a370 C=0x0        Y=0x563e4a86a3b0 E=0x0        P=0x563e4a86a2b0 F=0 L=0 S=6
N=0x563e4a86a3b0 C=0x0        Y=0x0        E=0x563e4a86a370 P=0x563e4a86a2b0 F=0 L=6 S=6
#  (0(0,5)(6,11)11)

N=0x563e4a86a2b0 C=0x563e4a86a430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x563e4a86a430 C=0x563e4a86a370 Y=0x0        E=0x0        P=0x563e4a86a2b0 F=4 L=0 S=12
N=0x563e4a86a370 C=0x563e4a86a2f0 Y=0x563e4a86a3b0 E=0x0        P=0x563e4a86a430 F=0 L=0 S=6
N=0x563e4a86a2f0 C=0x0        Y=0x563e4a86a330 E=0x0        P=0x563e4a86a370 F=0 L=0 S=2
N=0x563e4a86a330 C=0x0        Y=0x563e4a86a3f0 E=0x563e4a86a2f0 P=0x563e4a86a370 F=0 L=2 S=2
N=0x563e4a86a3f0 C=0x0        Y=0x0        E=0x563e4a86a330 P=0x563e4a86a370 F=0 L=4 S=2
N=0x563e4a86a3b0 C=0x0        Y=0x0        E=0x563e4a86a370 P=0x563e4a86a430 F=0 L=6 S=6
#  (0(0(0(0,1)(2,3)(4,5)5)(6,11)11|F)11)

#  (0(0(0,1)(2,3)(4,5)5)(6,11)11|F)
N=0x563e4a86a2b0 C=0x563e4a86a430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x563e4a86a430 C=0x563e4a86a2f0 Y=0x0        E=0x0        P=0x563e4a86a2b0 F=4 L=0 S=12
N=0x563e4a86a2f0 C=0x0        Y=0x563e4a86a330 E=0x0        P=0x563e4a86a430 F=0 L=0 S=2
N=0x563e4a86a330 C=0x0        Y=0x563e4a86a3f0 E=0x563e4a86a2f0 P=0x563e4a86a430 F=0 L=2 S=2
N=0x563e4a86a3f0 C=0x0        Y=0x563e4a86a3b0 E=0x563e4a86a330 P=0x563e4a86a430 F=0 L=4 S=2
N=0x563e4a86a3b0 C=0x0        Y=0x0        E=0x563e4a86a3f0 P=0x563e4a86a430 F=0 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)(6,11)11|F)11)

N=0x563e4a86a2b0 C=0x563e4a86a430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x563e4a86a430 C=0x563e4a86a2f0 Y=0x0        E=0x0        P=0x563e4a86a2b0 F=4 L=0 S=12
N=0x563e4a86a2f0 C=0x0        Y=0x563e4a86a330 E=0x0        P=0x563e4a86a430 F=0 L=0 S=2
N=0x563e4a86a330 C=0x0        Y=0x563e4a86a3b0 E=0x563e4a86a2f0 P=0x563e4a86a430 F=0 L=2 S=2
N=0x563e4a86a3b0 C=0x0        Y=0x563e4a86a3f0 E=0x563e4a86a330 P=0x563e4a86a430 F=0 L=4 S=6
N=0x563e4a86a3f0 C=0x0        Y=0x0        E=0x563e4a86a3b0 P=0x563e4a86a430 F=0 L=10 S=2
#  (0(0(0,1)(2,3)(4,9)(10,11)11|F)11)
#------------------------
N=0x563e4a86a2b0 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
#  (0,3)

N=0x563e4a86a2b0 C=0x563e4a86a430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
N=0x563e4a86a430 C=0x0        Y=0x563e4a86a2f0 E=0x0        P=0x563e4a86a2b0 F=4 L=0 S=2
N=0x563e4a86a2f0 C=0x0        Y=0x0        E=0x563e4a86a430 P=0x563e4a86a2b0 F=4 L=2 S=2
#  (0(0,1|F)(2,3|F)3)

#------------------------
N=0x563e4a86a2b0 C=0x563e4a86a430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x563e4a86a430 C=0x563e4a86a330 Y=0x563e4a86a2f0 E=0x0        P=0x563e4a86a2b0 F=0 L=0 S=6
N=0x563e4a86a330 C=0x0        Y=0x563e4a86a3b0 E=0x0        P=0x563e4a86a430 F=0 L=0 S=2
N=0x563e4a86a3b0 C=0x0        Y=0x563e4a86a3f0 E=0x563e4a86a330 P=0x563e4a86a430 F=0 L=2 S=2
N=0x563e4a86a3f0 C=0x0        Y=0x0        E=0x563e4a86a3b0 P=0x563e4a86a430 F=0 L=4 S=2
N=0x563e4a86a2f0 C=0x0        Y=0x0        E=0x563e4a86a430 P=0x563e4a86a2b0 F=4 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)5)(6,11|F)11)

