          ORG         $8000
         
   START:
   
   MAIN   LINK        A6,#0
          MOVEA.L     #$00009000,A7
          PEA         w
          PEA         x
          PEA         y
          PEA         z
          JSR         COMPUTE
        
          LEA         4(A7),A7
          UNLK        A6
          TRAP        #14
         
  COMPUTE LINK       A6,#0
          MOVEM.L    D1-D5/A0-A3,-(SP)
          MOVEA.L    20(A6),A0
          MOVEA.L    16(A6),A1
          MOVEA.L    12(A6),A2
          MOVEA.L    8(A6),A3
          
          MOVE       (A1),D2
          MULU       D2,D2
          MULU       #5,D2
          
          MOVE       (A1),D3
          MOVE       (A2),D4
          MULU       #4,D3
          MULU       D4,D3
          
          MOVE       (A3),D5
          MULU       D5,D5
          
          SUB         D3,D2
          ADD         D2,D5
          MOVE        D5,D1
          MOVEM.L     (SP)+,D1-D5/A0-A3
          UNLK        A6
          RTS

         
          ORG       $9000
  w       DC.W        0
  x       DC.W        2
  y       DC.W        -5
  z       DC.W        3
      	  END         START