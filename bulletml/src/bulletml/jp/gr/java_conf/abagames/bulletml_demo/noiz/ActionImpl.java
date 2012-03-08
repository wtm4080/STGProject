/*
 * $Id: ActionImpl.java,v 1.5 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml.*;
import jp.gr.java_conf.abagames.bulletml_demo.*;

/**
 * Action status.
 *
 * @version $Revision: 1.5 $
 */
public class ActionImpl {
  static public int NOT_EXIST = -9999;

  public IActionChoice[] action;
  private int repeat;
  public int pc;
  private int waitCnt;
  private float aimSpeed, mvSpeed;
  private int mvspCnt;
  private float aimDrc, mvDrc;
  private boolean isAim;
  private int mvdrCnt;
  private float prvFireDrc, prvFireSpeed;
  private int acclCnt;
  private float aimMx, aimMy, mvMx, mvMy;

  private ActionImpl parent;
  private BulletImpl bullet;

  private GameManager gameManager;

  private float[] prms;

  public ActionImpl(GameManager gm) {
    gameManager = gm;
    pc = NOT_EXIST;
  }

  public void set(Action action, BulletImpl bullet) {
    this.action = action.getContent();
    repeat = 1; pc = -1;
    waitCnt = mvspCnt = mvdrCnt = acclCnt = 0;
    prvFireDrc = 0; prvFireSpeed = 1;
    this.bullet = bullet;
    parent = null;
    prms = null;
  }

  public void setParams(float[] prms) {
    this.prms = prms;
  }

  public void setRepeat(int repeat) {
    this.repeat = repeat;
  }

  public void setParent(ActionImpl parent) {
    this.parent = parent;
  }

  public void setMoveStatus(int mvdrCnt, float mvDrc, boolean isAim,
   int mvspCnt, float mvSpeed, int acclCnt, float mvMx, float mvMy) {
    this.mvdrCnt = mvdrCnt; this.mvDrc = mvDrc; this.isAim = isAim;
    this.mvspCnt = mvspCnt; this.mvSpeed = mvSpeed;
    this.acclCnt = acclCnt; this.mvMx = mvMx; this.mvMy = mvMy;
  }

  public void setPrvFireStatus(float pfd, float pfs) {
    prvFireDrc = pfd; prvFireSpeed = pfs;
  }

  public void vanish() {
    if ( parent != null ) {
      parent.vanish();
    }
    pc = NOT_EXIST;
  }

  private final String ABSOLUTE_KEYWORD = "absolute";
  private final String RELATIVE_KEYWORD = "relative";
  private final String SEQUENCE_KEYWORD = "sequence";
  private final String AIM_KEYWORD = "aim";

  public void move() {
    if ( mvspCnt > 0 ) {
      mvspCnt--;
      bullet.speed += mvSpeed;
    }
    if ( mvdrCnt > 0 ) {
      mvdrCnt--;
      if ( mvdrCnt == 0 ) {
        if ( isAim ) {
          bullet.direction += bullet.getAimDeg();
        }
      } else {
        bullet.direction += mvDrc;
      }
    }
    if ( acclCnt > 0 ) {
      acclCnt--;
      bullet.mx += mvMx;
      bullet.my += mvMy;
    }

    if ( pc == NOT_EXIST ) return;

    if ( waitCnt > 0 ) {
      waitCnt--;
      return;
    }

    for ( ; ; ) {

    pc++;
    if ( pc >= action.length ) {
      repeat--;
      if ( repeat <= 0 ) {
        pc = NOT_EXIST;
        if ( parent != null ) {
          parent.setMoveStatus(
           mvdrCnt, mvDrc, isAim, mvspCnt, mvSpeed, acclCnt, mvMx, mvMy);
          parent.setPrvFireStatus(prvFireDrc, prvFireSpeed);
          bullet.changeAction(this, parent);
        }
        break;
      } else {
        pc = 0;
      }
    }

    IActionChoice ac = action[pc];
    if ( ac instanceof Repeat ) {
      // Repeat action.
      ActionImpl newAction = gameManager.getActionImplInstance();
      if ( newAction != null ) {
        Repeat rp = (Repeat)ac;
        newAction.set(
         BulletmlNoizUtil.getActionElm(rp.getActionElm()), bullet);
        float[] actPrms = BulletmlNoizUtil.getActionParams(rp.getActionElm(), prms);
        if ( actPrms == null ) {
          newAction.setParams(prms);
        } else {
          newAction.setParams(actPrms);
        }
        newAction.setRepeat(BulletmlUtil.getIntValue(rp.getTimes(), prms));
        newAction.setParent(this);
        newAction.setMoveStatus(
         mvdrCnt, mvDrc, isAim, mvspCnt, mvSpeed, acclCnt, mvMx, mvMy);
        newAction.setPrvFireStatus(prvFireDrc, prvFireSpeed);
        bullet.changeAction(this, newAction);
        newAction.move();
        break;
      }
    } else if ( ac instanceof ActionElm ) {
      // Action.
      ActionImpl newAction = gameManager.getActionImplInstance();
      if ( newAction != null ) {
        IActionElmChoice aec = ((ActionElm)ac).getContent();
        newAction.set(BulletmlNoizUtil.getActionElm(aec), bullet);
        float[] actPrms = BulletmlNoizUtil.getActionParams(aec, prms);
        if ( actPrms == null ) {
          newAction.setParams(prms);
        } else {
          newAction.setParams(actPrms);
        }
        newAction.setRepeat(1);
        newAction.setParent(this);
        newAction.setMoveStatus(
         mvdrCnt, mvDrc, isAim, mvspCnt, mvSpeed, acclCnt, mvMx, mvMy);
        newAction.setPrvFireStatus(prvFireDrc, prvFireSpeed);
        bullet.changeAction(this, newAction);
        newAction.move();
        break;
      }
    } else if ( ac instanceof FireElm ) {
      // Fire action.
      IFireElmChoice fec = ((FireElm)ac).getContent();
      Fire fire = BulletmlNoizUtil.getFireElm(fec);
      float[] firePrms = BulletmlNoizUtil.getFireParams(fec, prms);
      BulletImpl bi = gameManager.getBulletImplInstance();
      if ( bi != null ) {
        if ( firePrms == null ) {
          bi.setParams(BulletmlNoizUtil.getBulletParams(fire.getBulletElm(), prms));
        } else {
          bi.setParams(firePrms);
        }
        bi.set(BulletmlNoizUtil.getBulletElm(fire.getBulletElm()),
         bullet.x, bullet.y, bullet.clrIdx+1);
        Direction d = fire.getDirection();
        if ( d == null ) {
          d = bi.drcElm;
        }
        float drc;
        if ( d != null ) {
          if ( firePrms  == null ) {
            drc = BulletmlUtil.getFloatValue(d.getContent(), prms);
          } else {
            drc = BulletmlUtil.getFloatValue(d.getContent(), firePrms);
          }
          String type = d.getType();
          if ( type != null ) {
            if ( type.equals(AIM_KEYWORD) )  {
              drc += bullet.getAimDeg();
            } else if ( type.equals(SEQUENCE_KEYWORD) ) {
              drc += prvFireDrc;
            } else if ( type.equals(RELATIVE_KEYWORD) ) {
              drc += bullet.direction;
            }
          }
        } else {
          drc = bullet.getAimDeg();
        }
        bi.direction = prvFireDrc = drc;
        Speed s = fire.getSpeed();
        if ( s == null ) {
          s = bi.spdElm;
        }
        float spd = 1;
        if ( s != null ) {
          if ( firePrms == null ) {
            spd = BulletmlUtil.getFloatValue(s.getContent(), prms);
          } else {
            spd = BulletmlUtil.getFloatValue(s.getContent(), firePrms);
          }
          String type = s.getType();
          if ( type != null && (type.equals(RELATIVE_KEYWORD) || type.equals(SEQUENCE_KEYWORD)) ) {
            spd += prvFireSpeed;
          }
        }
        bi.speed = prvFireSpeed = spd;
      }
    } else if ( ac instanceof ChangeSpeed ) {
      // Change speed action.
      Speed s = ((ChangeSpeed)ac).getSpeed();
      String type = s.getType();
      mvspCnt = BulletmlUtil.getIntValue(((ChangeSpeed)ac).getTerm(), prms);
      if ( type != null && type.equals(SEQUENCE_KEYWORD) ) {
        mvSpeed = BulletmlUtil.getFloatValue(s.getContent(), prms);
        //aimSpeed = bullet.speed + mvSpeed*mvspCnt;
      } else {
        aimSpeed = BulletmlUtil.getFloatValue(s.getContent(), prms);
        if ( type != null && (type.equals(RELATIVE_KEYWORD) || type.equals(SEQUENCE_KEYWORD)) ) {
          aimSpeed += bullet.speed;
        }
        mvSpeed = (aimSpeed - bullet.speed) / mvspCnt;
      }
    } else if ( ac instanceof ChangeDirection ) {
      // Change direction action.
      Direction d = ((ChangeDirection)ac).getDirection();
      String type = d.getType();
      mvdrCnt = BulletmlUtil.getIntValue(((ChangeDirection)ac).getTerm(), prms);
      if ( type != null && type.equals(SEQUENCE_KEYWORD) ) {
        isAim = false;
        mvDrc = BulletmlUtil.getFloatValue(d.getContent(), prms);
        //aimDrc = bullet.direction + mvDrc*mvdrCnt;
      } else {
        aimDrc = BulletmlUtil.getFloatValue(d.getContent(), prms);
        if ( type != null && type.equals(ABSOLUTE_KEYWORD) ) {
          isAim = false;
          mvDrc = (aimDrc - bullet.direction)%360;
        } else if ( type != null && type.equals(RELATIVE_KEYWORD) ) {
          isAim = false;
          aimDrc += bullet.direction;
          mvDrc = (aimDrc - bullet.direction)%360;
        } else {
          isAim = true;
          mvDrc = (aimDrc+bullet.getAimDeg() - bullet.direction)%360;
        }
        if ( mvDrc > 180 ) mvDrc -= 360;
        if ( mvDrc < -180 ) mvDrc += 360;
        mvDrc /= mvdrCnt;
      }
    } else if ( ac instanceof Accel ) {
      // Accel bullet.
      Accel al = (Accel)ac;
      Horizontal hrz = al.getHorizontal();
      acclCnt = BulletmlUtil.getIntValue(al.getTerm(), prms);
      if ( hrz != null ) {
        String type = hrz.getType();
        if ( type != null && type.equals(SEQUENCE_KEYWORD) ) {
          mvMx = BulletmlUtil.getFloatValue(hrz.getContent(), prms);
          //aimMx = bullet.mx + mvMx*acclCnt;
        } else {
          aimMx = BulletmlUtil.getFloatValue(hrz.getContent(), prms);
          if ( type != null && type.equals(RELATIVE_KEYWORD) ) {
            aimMx += bullet.mx;
          }
          mvMx = (aimMx - bullet.mx) / acclCnt;
        }
      }
      Vertical vtc = al.getVertical();
      if ( vtc != null ) {
        String type = vtc.getType();
        if ( type != null && type.equals(RELATIVE_KEYWORD) ) {
          mvMy = BulletmlUtil.getFloatValue(vtc.getContent(), prms);
          //aimMy = bullet.my + mvMy*acclCnt;
        } else {
          aimMy = BulletmlUtil.getFloatValue(vtc.getContent(), prms);
          if ( type != null && (type.equals(RELATIVE_KEYWORD) || type.equals(SEQUENCE_KEYWORD)) ) {
            aimMy += bullet.my;
          }
          mvMy = (aimMy - bullet.my) / acclCnt;
        }
      }
    } else if ( ac instanceof Wait ) {
      // Wait action.
      waitCnt = BulletmlUtil.getIntValue(((Wait)ac).getContent(), prms);
      break;
    } else if ( ac instanceof Vanish ) {
      // Vanish action.
      bullet.vanish();
      break;
    }

    }
  }
}
