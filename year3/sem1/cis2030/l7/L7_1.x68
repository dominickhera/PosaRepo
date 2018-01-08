        ORG         $8000
START

TOP	    MOVE.W      D1,D4
		ROR.W       #1,D4
        BCC         MATH
        ADD.W       D0,D2
MATH    CMP.W       #1,D1
        BEQ         EXIT
        LSL.W       #1,D0
        LSR.W       #1,D1
        BRA         TOP
        
EXIT    TRAP        #14
        END         START