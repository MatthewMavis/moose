C
      SUBROUTINE CREEP(DECRA,DESWA,STATEV,SERD,EC,ESW,P,QTILD,
     1     TEMP,DTEMP,PREDEF,DPRED,TIME,DTIME,CMNAME,LEXIMP,LEND,
     2     COORDS,NSTATV,NOEL,NPT,LAYER,KSPT,KSTEP,KINC)
C
C      INCLUDE 'ABA_PARAM.INC'
C     
      CHARACTER*80 CMNAME
C     
      DIMENSION DECRA(5),DESWA(5),STATEV(*),PREDEF(*),DPRED(*),
     1     TIME(2),COORDS(*),EC(2),ESW(2)
C     
C     DEFINE CONSTANTS
C     
      A=2.5E-27
      SIG0=10
      AN=-0.2
C     
      T1=EXP(QTILD/SIG0)
      T2=EXP(-QTILD/SIG0)
      IF (T1-T2.EQ.0.0) THEN
         DECRA(1) = 0.0
      ELSE
         DECRA(1) = A*(.5*(T1-T2))**AN*DTIME
      END IF

      IF(LEXIMP.EQ.1) THEN
         IF (T1-T2.EQ.0.) THEN
            DECRA(5) = 0.0
         ELSE
            DECRA(5) = AN*A*(.5*(T1-T2))**(AN-1.)*DTIME/
     1           SIG0*.5*(T1+T2)
         END IF
      END IF
C     
      RETURN
      END
