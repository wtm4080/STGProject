/*
 * $Id: BulletmlNoizUtil.java,v 1.3 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml.*;
import jp.gr.java_conf.abagames.bulletml_demo.*;
import java.util.Hashtable;
import java.awt.TextArea;

/**
 * Utility class for BulletML with Noiz.
 *
 * @version $Revision: 1.3 $
 */
public class BulletmlNoizUtil {

  private static Hashtable bullets = new Hashtable();
  private static Hashtable actions = new Hashtable();
  private static Hashtable fires = new Hashtable();

  private static TextArea console;

  public static void setConsole(TextArea csl) {
    console = csl;
  }

  public static void clear() {
    bullets.clear();
    actions.clear();
    fires.clear();
  }

  public static void addBullet(Bullet blt) {
    bullets.put(blt.getLabel(), blt);
  }

  public static void addAction(Action act) {
    actions.put(act.getLabel(), act);
  }

  public static void addFire(Fire fre) {
    fires.put(fre.getLabel(), fre);
  }

  public static Bullet getBulletElm(IBulletElmChoice bec) {
    if ( bec instanceof BulletRef ) {
      String label = ((BulletRef)bec).getLabel();
      Bullet blt = (Bullet)bullets.get(label);
      if ( blt == null && console != null ) {
        console.append("unknown bullet label: " + label + "\n");
      }
      return blt;
    } else if ( bec instanceof Bullet ) {
      return (Bullet)bec;
    }
    return null;
  }

  public static float[] getBulletParams(IBulletElmChoice bec, float[] prms) {
    if ( bec instanceof BulletRef ) {
      BulletRef br = (BulletRef)bec;
      float[] prm = new float[br.getParamCount()];
      for ( int i=prm.length-1; i>=0 ; i-- ) {
        prm[i] = BulletmlUtil.getFloatValue(br.getParam(i).getContent(), prms);
      }
      return prm;
    }
    return null;
  }

  public static Action getActionElm(IActionElmChoice aec) {
    if ( aec instanceof ActionRef ) {
      String label = ((ActionRef)aec).getLabel();
      Action act = (Action)actions.get(label);
      if ( act == null && console != null ) {
        console.append("unknown action label: " + label + "\n");
      }
      return act;
    } else if ( aec instanceof Action ) {
      return (Action)aec;
    }
    return null;
  }

  public static float[] getActionParams(IActionElmChoice aec, float[] prms) {
    if ( aec instanceof ActionRef ) {
      ActionRef ar = (ActionRef)aec;
      float[] prm = new float[ar.getParamCount()];
      for ( int i=prm.length-1; i>=0 ; i-- ) {
        prm[i] = BulletmlUtil.getFloatValue(ar.getParam(i).getContent(), prms);
      }
      return prm;
    }
    return null;
  }

  public static Fire getFireElm(IFireElmChoice fec) {
    if ( fec instanceof FireRef ) {
      String label = ((FireRef)fec).getLabel();
      Fire fire = (Fire)fires.get(label);
      if ( fire == null && console != null ) {
        console.append("unknown fire label: " + label + "\n");
      }
      return fire;
    } else if ( fec instanceof Fire ) {
      return (Fire)fec;
    }
    return null;
  }

  public static float[] getFireParams(IFireElmChoice fec, float[] prms) {
    if ( fec instanceof FireRef ) {
      FireRef fr = (FireRef)fec;
      float[] prm = new float[fr.getParamCount()];
      for ( int i=prm.length-1; i>=0 ; i-- ) {
        prm[i] = BulletmlUtil.getFloatValue(fr.getParam(i).getContent(), prms);
      }
      return prm;
    }
    return null;
  }
}
