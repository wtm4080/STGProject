/*
 * $Id: Expression.java,v 1.1 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo;

import jp.gr.java_conf.abagames.bulletml.*;
import java.util.Random;

/**
 * Turn expression into RPN.
 *
 * @version $Revision: 1.1 $
 */
public class Expression {
  private static Random rnd = new Random();

  private static final int MAX_LENGTH = 128;

  public static final int STACK_VARIABLE = 11;
  public static final int STACK_RANK = -2;
  public static final int STACK_RAND = -1;
  public static final int STACK_NUM = 0;
  public static final int PLUS = 1;
  public static final int MINUS = 2;
  public static final int MULTIPLE = 3;
  public static final int DIVISION = 4;
  public static final int MODULO = 5;

  private float[] num = new float[MAX_LENGTH];
  private int[] opr = new int[MAX_LENGTH];
  private int idx;

  private float[] stack = new float[MAX_LENGTH];

  public Expression() {
    idx = 0;
  }

  private float calcOp(int op, float n1, float n2) {
    switch ( op ) {
    case PLUS:
      return n1 + n2;
    case MINUS:
      return n1 - n2;
    case MULTIPLE:
      return n1 * n2;
    case DIVISION:
      return n1 / n2;
    case MODULO:
      return n1 % n2;
    }
    return 0;
  }

  public void setOperator(int op) {
    if ( idx >= MAX_LENGTH ) return;
    if ( opr[idx-1]==STACK_NUM && opr[idx-2]==STACK_NUM ) {
      num[idx-2] = calcOp(op, num[idx-2], num[idx-1]);
      idx--;
    } else {
      opr[idx] = op;
      idx++;
    }
  }

  public void push(float nm, int vr) {
    if ( idx >= MAX_LENGTH ) return;
    num[idx] = nm; opr[idx] = vr;
    idx++;
  }

  public float calc(float[] prms) {
    int stkIdx = 0;
    for ( int i=0 ; i<idx ; i++ ) {
      switch ( opr[i] ) {
      case STACK_NUM:
        stack[stkIdx] = num[i];
        stkIdx++;
        break;
      case STACK_RAND:
        stack[stkIdx] = rnd.nextFloat();
        stkIdx++;
        break;
      case STACK_RANK:
        stack[stkIdx] = BulletmlUtil.getRank();
        stkIdx++;
        break;
      default:
        if ( opr[i] >= STACK_VARIABLE ) {
          stack[stkIdx] = prms[opr[i]-STACK_VARIABLE];
          stkIdx++;
        } else {
          stack[stkIdx-2] = calcOp(opr[i], stack[stkIdx-2], stack[stkIdx-1]);
          stkIdx--;
        }
        break;
      }
    }
    return stack[0];
  }
}
