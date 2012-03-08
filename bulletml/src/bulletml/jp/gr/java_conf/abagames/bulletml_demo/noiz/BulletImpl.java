/*
 * $Id: BulletImpl.java,v 1.4 2001/05/14 14:21:58 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml.*;
import jp.gr.java_conf.abagames.bulletml_demo.*;
import jp.gr.java_conf.abagames.util.*;

/**
 * Bullet implementation.
 *
 * @version $Revision: 1.4 $
 */
public class BulletImpl {
  public static final int NOT_EXIST = -9999;

  private final int SCREEN_WIDTH_16 = Noiz.SCREEN_WIDTH<<4;
  private final int SCREEN_HEIGHT_16 = Noiz.SCREEN_HEIGHT<<4;
  private final int[] BULLET_COLOR = {
     0xffffff, 0xffaaaa, 0xaaffaa, 0xaaaaff,
  };

  private final int ACTION_MAX = 8;

  private ActionImpl[] action = new ActionImpl[ACTION_MAX];
  private int acIdx;

  public int x, y, px, py;

  public Direction drcElm;
  public Speed spdElm;
  public float direction, speed;

  public float mx, my;

  public int clrIdx;

  private int cnt;

  private GameManager gameManager;

  private float[] prms;

  public BulletImpl(GameManager gm) {
    gameManager = gm;
    x = NOT_EXIST;
  }

  public void changeAction(ActionImpl bfr, ActionImpl aft) {
    for ( int i=0 ; i<acIdx ; i++ ) {
      if ( action[i].equals(bfr) ) {
        action[i] = aft;
        return;
      }
    }
  }

  public void set(IActionElmChoice[] aec, int x, int y, int ci) {
    this.x = px = x; this.y = py = y;
    mx = my = 0;
    clrIdx = ci&3;
    cnt = 0;
    acIdx = 0;
    for ( int i=0 ; i<aec.length ; i++ ) {
      action[acIdx] = gameManager.getActionImplInstance();
      if ( action[acIdx] == null ) break;
      action[acIdx].set(BulletmlNoizUtil.getActionElm(aec[i]), this);
      float[] actPrms = BulletmlNoizUtil.getActionParams(aec[i], prms);
      if ( actPrms == null ) {
        action[acIdx].setParams(prms);
      } else {
        action[acIdx].setParams(actPrms);
      }
      acIdx++;
      if ( acIdx >= ACTION_MAX ) break;
    }
  }

  public void set(Bullet bullet, int x, int y, int ci) {
    drcElm = bullet.getDirection();
    spdElm = bullet.getSpeed();
    IActionElmChoice[] aec = bullet.getActionElm();
    set(aec, x, y, ci);
  }

  public void setParams(float[] prms) {
    this.prms = prms;
  }

  public float getAimDeg() {
    //return (float)DegUtil.getDeg(gameManager.xp - x, gameManager.yp - y)
    // * (float)Math.PI / 128;
    return (float)DegUtil.getDeg(gameManager.xp - x, gameManager.yp - y)
     * 360 / SCTable.TABLE_SIZE;
  }

  public void vanish() {
    for ( int i=0 ; i<acIdx ; i++ ) {
      action[i].vanish();
    }
    x = NOT_EXIST;
  }

  public boolean isAllActionFinished() {
    for ( int i=0 ; i<acIdx ; i++ ) {
      if ( action[i].pc != ActionImpl.NOT_EXIST ) {
        return false;
      }
    }
    return true;
  }

  public void move() {
    for ( int i=0 ; i<acIdx ; i++ ) {
      action[i].move();
    }

    cnt++;
    //int d = (int)(direction*SCTable.TABLE_SIZE/Math.PI/2);
    int d = (int)(direction*SCTable.TABLE_SIZE/360);
    d &= (SCTable.TABLE_SIZE-1);

    int mvx = ((int)(speed*SCTable.sintbl[d])>>3) + (int)(mx*32);
    int mvy = ((int)(-speed*SCTable.costbl[d])>>3) + (int)(my*32);
    x += mvx;
    y += mvy;
    if ( cnt < 4 ) {
      px = x - mvx;
      py = y - mvy;
    } else if ( cnt < 8 ) {
      px = x - (mvx<<1);
      py = y - (mvy<<1);
    } else {
      px = x - (mvx<<2);
      py = y - (mvy<<2);
    }

    switch ( gameManager.hvStat ) {
    case 0:
      if ( px < 0
        || px >= SCREEN_WIDTH_16
        || py < -(SCREEN_HEIGHT_16>>2)
        || py >= SCREEN_HEIGHT_16 ) {
	  vanish();
        }
        break;
    case 1:
      if ( px < 0
        || px >= SCREEN_WIDTH_16+(SCREEN_WIDTH_16>>2)
        || py < 0
        || py >= SCREEN_HEIGHT_16 ) {
	  vanish();
        }
        break;
    }
  }

  public void draw() {
    gameManager.screen.drawLine((x>>4), (y>>4),
                                (px>>4), (py>>4), BULLET_COLOR[clrIdx]);
  }
}
