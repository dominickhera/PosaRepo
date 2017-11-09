 			  ORG     $8000
 
  solveQuad   LINK    A6,#0
		      MOVE.W  8(A6),D2
			  MULU.W  #5,D2
              MULU.W  D0,D2
              MOVE    8(A6),D3
              MULU    #2,D3
              SUB     D3,D2
              ADD     #6,D2
              MOVE    D2,D1
              UNLK    A6
              RTS
  START:
  
  MAIN   MOVE.W      D1,D4
         MOVE        D0,-2(A6)
         MOVE        -2(A6),-(A7)
         JSR         solveQuad

    
		 TRAP        #14
     	 END         START