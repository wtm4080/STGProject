/*
 * $Id: DegUtil.java,v 1.1 2001/05/11 15:00:49 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.util;

/**
 * Cordinate chcanged into the angle.
 *
 * @version $Revision: 1.1 $
 */
public class DegUtil {
  /*private static final int DIV = 360;
  static int[] tantab = new int[258];

  static {
    int i, d=0;
    double od = Math.PI*2 / DIV;
    for ( i=0 ; i<256 ; i++ ) {
      while ( (int)(Math.sin(d*od)/Math.cos(d*od)*256)<i ) d++;
      tantab[i] = d;
    }
    tantab[256] = 128;
    tantab[257] = 128;
  }*/

private static final int DIV = 256;

private static final int[] tantbl = {
0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3,
3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8,
8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10,
10, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 13, 13,
13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15,
15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17,
17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19,
19, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21,
21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23,
23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25,
25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30,
30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31,
31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
32, 32};

  public static int getDeg(int x, int y) {
    int tx, ty;
    int f, od, tn;

    if ( x==0 && y==0 ) {
      return(0);
    }

    if ( x < 0 ) {
      tx = -x;
      if ( y < 0 ) {
        ty = -y;
        if ( tx > ty ) {
          f = 1;
          od = DIV*3/4; tn = ty*256/tx;
        } else {
          f = -1;
          od = DIV; tn = tx*256/ty;
        }
      } else {
        ty = y;
        if ( tx > ty ) {
          f = -1;
          od = DIV*3/4; tn=ty*256/tx;
        } else {
          f=1;
          od = DIV/2; tn=tx*256/ty;
        }
      }
    } else {
      tx = x;
      if ( y < 0 ) {
        ty = -y;
        if ( tx > ty ) {
          f = -1;
          od = DIV/4; tn = ty*256/tx;
        } else {
          f = 1;
          od = 0; tn = tx*256/ty;
        }
      } else {
        ty = y;
        if ( tx > ty ) {
          f = 1;
          od = DIV/4; tn = ty*256/tx;
        } else {
          f = -1;
          od = DIV/2; tn = tx*256/ty;
        }
      }
    }
    return(od+tantbl[tn]*f);
  }
}
