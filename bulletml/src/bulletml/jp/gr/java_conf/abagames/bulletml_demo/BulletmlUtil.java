/*
 * $Id: BulletmlUtil.java,v 1.3 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo;

import jp.gr.java_conf.abagames.bulletml.*;
import java.util.Hashtable;

/**
 * Utility class for BulletML.
 *
 * @version $Revision: 1.3 $
 */
public class BulletmlUtil {
  private static Hashtable expressions = new Hashtable();

  public static int getIntValue(String v, float[] prms) {
    return (int)evalExpression(v, prms);
  }

  public static float getFloatValue(String v, float[] prms) {
    return evalExpression(v, prms);
  }

  private static char[] expChr;
  private static float rank = 0.5f;

  public static void setRank(float rk) {
    rank = rk;
  }

  public static float getRank() {
    return rank;
  }

  private static void evalFloatValue(Expression ep, int stIdx, int lgt, float sign) {
    if ( expChr[stIdx] == '$' ) {
      String label = new String(expChr, stIdx+1, lgt-1);
      if ( label.equals("rand") ) {
        //return rnd.nextFloat();
        ep.push(0, Expression.STACK_RAND);
      } else if ( label.equals("rank") ) {
        //return rank;
        ep.push(0, Expression.STACK_RANK);
      } else {
        int idx;
        try {
          idx = new Integer(label).intValue()-1;
        } catch ( NumberFormatException e ) {
          //return 0;
          ep.push(0, Expression.STACK_NUM);
          return;
        }
        //return prms[idx];
        ep.push(0, Expression.STACK_VARIABLE+idx);
      }
    } else {
      try {
        //return new Float(new String(expChr, stIdx, lgt)).floatValue();
        ep.push(new Float(new String(expChr, stIdx, lgt)).floatValue()*sign,
         Expression.STACK_NUM);
      } catch ( NumberFormatException e ) {
        //return 0;
        ep.push(0, Expression.STACK_NUM);
      }
    }
  }

  private static void evalExpPart(Expression ep, int stIdx, int edIdx) {
    int op[] = new int[] {-1, -1};
    while (expChr[stIdx]=='(' && expChr[edIdx-1]==')') {
      stIdx++;
      edIdx--;
    }
    for ( int i = edIdx-1; i >= stIdx ; i-- ) {
      char c = expChr[i];
      if ( c == ')' ) {
        do {
          i--;
        } while ( expChr[i] != '(' );
      } else if ( op[0] < 0 && (c=='*' || c=='/' || c=='%') ) {
	op[0] = i;
      } else if ( c=='+' || c=='-' ) {
	op[1] = i;
	break;
      }
    }
    if ( op[1] < 0 ) {
      if ( op[0] < 0 ) {
        //return evalFloatValue(stIdx, edIdx-stIdx);
        evalFloatValue(ep, stIdx, edIdx-stIdx, 1);
      } else {
	switch(expChr[op[0]]) {
	case '*':
	  //return evalExpPart(stIdx, op[0]) * evalExpPart(op[0]+1, edIdx);
	  evalExpPart(ep, stIdx, op[0]);
          evalExpPart(ep, op[0]+1, edIdx);
          ep.setOperator(Expression.MULTIPLE);
          break;
	case '/':
	  //return evalExpPart(stIdx, op[0]) / evalExpPart(op[0]+1, edIdx);
	  evalExpPart(ep, stIdx, op[0]);
          evalExpPart(ep, op[0]+1, edIdx);
          ep.setOperator(Expression.DIVISION);
          break;
	case '%':
	  //return evalExpPart(stIdx, op[0]) % evalExpPart(op[0]+1, edIdx);
	  evalExpPart(ep, stIdx, op[0]);
          evalExpPart(ep, op[0]+1, edIdx);
          ep.setOperator(Expression.MODULO);
          break;
	}
      }
    } else {
      if ( op[1] == stIdx ) {
	switch (expChr[op[1]]) {
	case '-':
          //return -evalFloatValue(stIdx+1, edIdx-stIdx-1);
          evalFloatValue(ep, stIdx+1, edIdx-stIdx-1, -1);
          break;
	case '+':
          //return  evalFloatValue(stIdx+1, edIdx-stIdx-1);
          evalFloatValue(ep, stIdx+1, edIdx-stIdx-1, 1);
          break;
	}
      } else {
	switch(expChr[op[1]]) {
	case '+':
	  //return evalExpPart(stIdx, op[1]) + evalExpPart(op[1]+1, edIdx);
	  evalExpPart(ep, stIdx, op[1]);
          evalExpPart(ep, op[1]+1, edIdx);
          ep.setOperator(Expression.PLUS);
          break;
	case '-':
	  //return evalExpPart(stIdx, op[1]) - evalExpPart(op[1]+1, edIdx);
	  evalExpPart(ep, stIdx, op[1]);
          evalExpPart(ep, op[1]+1, edIdx);
          ep.setOperator(Expression.MINUS);
          break;
	}
      }
    }
  }

  public static float evalExpression(String exp, float[] p) {
    Expression ep = (Expression)expressions.get(exp);
    if ( ep == null ) {
      expChr = new char[exp.length()];
      int ecIdx = 0;
      boolean skip = false;
      StringBuffer buf = new StringBuffer(exp);
      int depth = 0;
      boolean balance = true;
      char ch;
      for( int i=0 ; i<buf.length() ; i++ ) {
        ch = buf.charAt(i);
        switch(ch) {
        case ' ':
        case '\n':
          skip = true;
          break;
        case ')':
          depth--;
          if ( depth < 0 ) balance = false;
          break;
        case '(':
          depth++;
          break;
        }
        if ( skip ) {
          skip = false;
        } else {
          expChr[ecIdx] = ch;
          ecIdx++;
        }
      }
      if ( depth != 0 || !balance ) {
        return 0;
      }
      ep = new Expression();
      evalExpPart(ep, 0, ecIdx);
      expressions.put(exp, ep);
    }
    return ep.calc(p);
  }
}
