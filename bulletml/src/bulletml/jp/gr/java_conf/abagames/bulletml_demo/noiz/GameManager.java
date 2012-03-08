/*
 * $Id: GameManager.java,v 1.5 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml.*;
import jp.gr.java_conf.abagames.util.*;
import java.io.*;
import java.util.Vector;
import java.util.Random;
import java.awt.TextArea;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXParseException;
import org.w3c.dom.Document;

/**
 * Handle game status.
 *
 * @version $Revision: 1.5 $
 */
public class GameManager implements ITime {

  private final int BULLET_NOT_EXIST = BulletImpl.NOT_EXIST;

  private final int BULLET_MAX = 256;
  private BulletImpl[] bullet = new BulletImpl[BULLET_MAX];
  private int bltIdx = 0;

  private final int ACTION_MAX = 1024;
  private ActionImpl[] action = new ActionImpl[ACTION_MAX];
  private int actIdx = 0;

  private final int FRAG_MAX = 16;
  private Frag[] frag = new Frag[FRAG_MAX];
  private int frgIdx = 0;

  public void initBullets() {
    for ( int i=0 ; i<bullet.length ; i++ ) {
      bullet[i] = new BulletImpl(this);
    }
    for ( int i=0 ; i<action.length ; i++ ) {
      action[i] = new ActionImpl(this);
    }
    for ( int i=0 ; i<frag.length ; i++ ) {
      frag[i] = new Frag(this);
    }
  }

  private void resetBullets() {
    int i;
    for ( i=0 ; i<BULLET_MAX ; i++ ) {
      bullet[i].x = BULLET_NOT_EXIST;
    }
  }

  public BulletImpl getBulletImplInstance() {
    for ( int i=BULLET_MAX-1 ; i>=0 ; i-- ) {
      bltIdx++; bltIdx &= (BULLET_MAX-1);
      if ( bullet[bltIdx].x == BULLET_NOT_EXIST ) {
        return bullet[bltIdx];
      }
    }
    return null;
  }

  public ActionImpl getActionImplInstance() {
    for ( int i=ACTION_MAX-1 ; i>=0 ; i-- ) {
      actIdx++; actIdx &= (ACTION_MAX-1);
      if ( action[actIdx].pc == ActionImpl.NOT_EXIST ) {
        return action[actIdx];
      }
    }
    return null;
  }

  public void addFrag(int x, int y) {
    frgIdx++; frgIdx &= (FRAG_MAX-1);
    frag[frgIdx].set(x, y);
  }

// ported from Palm

public int xp, yp;
private int pxp, pyp;

void startGame() {
  mouseX = 160; mouseY = 240;
  xp = 160<<4; yp = 240<<4;
  pxp = xp+1; pyp = yp;
}

private void hitBullet() {
  for ( int i=4 ; i>=0 ; i-- ) {
    addFrag(xp, yp);
  }
}

private final int CLS_WIDTH = 32;
private final int PEN_COLOR = 0xffddbb;

public final void movePen() {
  int px, py;
  Boolean pd;
  int i;
  BulletImpl bl;
  int a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y;
  int a, b, c, d, e, f, dnm;
  int mk;
  int x, y;
  int oxp, oyp;

  pxp = xp; pyp = yp;
  if ( mouseX >= 0 && mouseX < Noiz.SCREEN_WIDTH
   && mouseY >=0 && mouseY < Noiz.SCREEN_HEIGHT ) {
    xp = (mouseX<<4)+8;
    yp = (mouseY<<4)+8;
  }
  screen.drawLine(pxp>>4, pyp>>4, xp>>4, yp>>4, PEN_COLOR);
  oxp = xp; oyp = yp;
  switch ( hvStat ) {
  case 0:
    if ( xp < pxp ) {
      xp -= CLS_WIDTH; pxp += CLS_WIDTH;
      a1x =  xp-CLS_WIDTH; a2x = pxp+CLS_WIDTH;
    } else {
      pxp -= CLS_WIDTH; xp += CLS_WIDTH;
      a1x = pxp-CLS_WIDTH; a2x =  xp+CLS_WIDTH;
    }
    if ( yp < pyp ) {
      a1y =  yp-CLS_WIDTH; a2y = pyp+CLS_WIDTH;
    } else {
      a1y = pyp-CLS_WIDTH; a2y =  yp+CLS_WIDTH;
    }
    break;
  case 1:
    if ( xp < pxp ) {
      a1x =  xp-CLS_WIDTH; a2x = pxp+CLS_WIDTH;
    } else {
      a1x = pxp-CLS_WIDTH; a2x =  xp+CLS_WIDTH;
    }
    if ( yp < pyp ) {
      yp -= CLS_WIDTH; pyp += CLS_WIDTH;
      a1y =  yp-CLS_WIDTH; a2y = pyp+CLS_WIDTH;
    } else {
      pyp -= CLS_WIDTH; yp += CLS_WIDTH;
      a1y = pyp-CLS_WIDTH; a2y =  yp+CLS_WIDTH;
    }
    break;
  default:
    a1x = a2x = a1y = a2y = 0;
    break;
  }

  for ( i=BULLET_MAX-1 ; i>=0 ; i-- ) {
    bl = bullet[i];
    if ( bl.x != BULLET_NOT_EXIST ) {
      if ( bl.y < bl.py ) {
	b1y = bl.y-CLS_WIDTH; b2y = bl.py+CLS_WIDTH;
      } else {
	b1y = bl.py-CLS_WIDTH; b2y = bl.y+CLS_WIDTH;
      }
      if ( a2y>=b1y && b2y>=a1y ) {
	if ( bl.x < bl.px ) {
	  b1x = bl.x-CLS_WIDTH; b2x = bl.px+CLS_WIDTH;
	} else {
	  b1x = bl.px-CLS_WIDTH; b2x = bl.x+CLS_WIDTH;
	}
	if ( a2x>=b1x && b2x>=a1x ) {
	  a = yp - pyp;
	  b = pxp - xp;
	  c = pxp*yp - pyp*xp;
	  d = bl.y - bl.py;
	  e = bl.px - bl.x;
	  f = bl.px*bl.y
	    - bl.py*bl.x;
	  dnm = b*d - a*e;
	  if ( dnm != 0 ) {
	    x = (b*f - c*e) / dnm;
	    y = (c*d - a*f) / dnm;
            if ( a1x<=x && x<=a2x && a1y<=y && y<=a2y &&
              b1x<=x && x<=b2x && b1y<=y && y<=b2y ) {
		hitBullet();
		return;
            }
	  }
	}
      }
    }
  }
  xp = oxp; yp = oyp;
}

  // BulletML handler.

  private IActionElmChoice[] topAction;

  public void loadBulletML(String document, final TextArea console) {
    try {
      ErrorHandler errorHandler = new ErrorHandler() {
        public void error(SAXParseException e) {
          console.append("error : ");
          console.append(e.getMessage());
          console.append("\n");
        }
        public void fatalError(SAXParseException e) {
          console.append("fatal error : ");
          console.append(e.getMessage());
          console.append("\n");
        }
        public void warning(SAXParseException e) {
          console.append("warning : ");
          console.append(e.getMessage());
          console.append("\n");
        }
      };
      Document doc = UJAXP.getValidDocument(
       new StringReader(document), errorHandler);
      Bulletml bulletML = new Bulletml(doc);
      String type = bulletML.getType();
      if (  type != null  ) {
        if ( type.equals("vertical") ) {
          noiz.selectVrtHrz(0);
        } else if ( type.equals("horizontal") ) {
          noiz.selectVrtHrz(1);
        }
      }
      IBulletmlChoice[] bmc = bulletML.getContent();
      Vector aecVct = new Vector();
      BulletmlNoizUtil.clear();
      for ( int i=0 ; i<bmc.length ; i++ ) {
        IBulletmlChoice be = bmc[i];
        if ( be instanceof Action ) {
          Action act = (Action)be;
          if ( act.getLabel().startsWith("top") ) {
            aecVct.addElement(act);
          }
          BulletmlNoizUtil.addAction(act);
        } else if ( be instanceof Bullet ) {
          BulletmlNoizUtil.addBullet((Bullet)be);
        } else if ( be instanceof Fire ) {
          BulletmlNoizUtil.addFire((Fire)be);
        }
      }
      topAction = new IActionElmChoice[aecVct.size()];
      aecVct.copyInto(topAction);
    } catch ( Exception e ) {
      e.printStackTrace();
    }
  }

  public int hvStat;

  public void setHVStat(int hvs) {
    hvStat = hvs;
  }

  private BulletImpl topBullet;
  private int shotCnt = 0;
  private Random rnd = new Random();

  private void addBullets() {
    if ( topBullet != null &&
         topBullet.x != BulletImpl.NOT_EXIST &&
         !topBullet.isAllActionFinished() ) return;
    shotCnt--;
    if ( shotCnt > 0 ) return;
    shotCnt = 60;
    topBullet = getBulletImplInstance();
    if ( topBullet == null ) return;
    switch ( hvStat ) {
    case 0:
      topBullet.set(topAction,
       (120+Math.abs(rnd.nextInt())%80)<<4, (20+Math.abs(rnd.nextInt())%40)<<4, 0);
      break;
    case 1:
      topBullet.set(topAction,
       (300-Math.abs(rnd.nextInt())%40)<<4, (120+Math.abs(rnd.nextInt())%80)<<4, 0);
      break;
    }
    topBullet.speed = 0; topBullet.direction = 0;
  }

  // java lifecycle management

  private int mouseX, mouseY;

  public final void setMousePos(int x, int y) {
    mouseX = x; mouseY = y;
  }

  private final int INTERVAL = 16;

  private Timer timerTrd;
  private Noiz noiz;
  public Screen screen;

  public void init(Noiz noiz, Screen screen) {
    this.noiz = noiz;
    this.screen = screen;
  }

  public void start() {
    startGame();
    timerTrd = new Timer(this);
    timerTrd.activate(INTERVAL, false);
  }

  public void restart() {
    if ( timerTrd != null ) {
      timerTrd.deactivate();
    }
  }

  private synchronized void waitFrame() {
    try {
      wait();
    } catch ( InterruptedException e ) {}
  }

  public synchronized final void notifyFrame() {
    notifyAll();
  }

  private void moveBullets() {
    for ( int i=BULLET_MAX-1 ; i>=0 ; i-- ) {
      if ( bullet[i].x != BULLET_NOT_EXIST ) {
        bullet[i].move();
      }
    }
  }

  private void drawBullets() {
    for ( int i=BULLET_MAX-1 ; i>=0 ; i-- ) {
      if ( bullet[i].x != BULLET_NOT_EXIST ) {
        bullet[i].draw();
      }
    }
  }

  private void moveFrags() {
    for ( int i=FRAG_MAX-1 ; i>=0 ; i-- ) {
      if ( frag[i].cnt != Frag.NOT_EXIST ) {
        frag[i].move();
      }
    }
  }

  private void drawFrags() {
    for ( int i=FRAG_MAX-1 ; i>=0 ; i-- ) {
      if ( frag[i].cnt != Frag.NOT_EXIST ) {
        frag[i].draw();
      }
    }
  }


  private long prvTickCount = 0;

  private void gameWakeUp() {
    screen.clear();
    long nowTick = System.currentTimeMillis();
    int frame = (int)(nowTick-prvTickCount) / INTERVAL;
    if ( frame <= 0 ) {
      frame = 1;
      prvTickCount = nowTick;
    } else if ( frame > 5 ) {
      frame = 5;
      prvTickCount = nowTick;
    } else {
      prvTickCount += frame*INTERVAL;
    }
    for ( int i=0 ; i<frame ; i++ ) {
      addBullets();
      moveBullets();
      moveFrags();
    }
    drawBullets();
    drawFrags();
    movePen();
    screen.swap();
  }

  public final void wakeUp() {
    try {
      gameWakeUp();
    } catch ( Exception e ) {
      noiz.exceptionOccured(e);
    }
    waitFrame();
  }
}
