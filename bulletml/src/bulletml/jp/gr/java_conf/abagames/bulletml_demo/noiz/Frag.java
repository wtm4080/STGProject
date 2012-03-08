/*
 * $Id: Frag.java,v 1.2 2001/05/14 14:21:58 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml.*;
import jp.gr.java_conf.abagames.bulletml_demo.*;
import jp.gr.java_conf.abagames.util.*;
import java.util.Random;

/**
 * Hit frag fireworks.
 *
 * @version $Revision: 1.2 $
 */
public class Frag {
  public final static int NOT_EXIST = -1;

  private int x, y, mx, my, px, py;
  public int cnt;

  private static Random rnd = new Random();

  private GameManager gameManager;

  public Frag(GameManager gameManager) {
    this.gameManager = gameManager;
    cnt = NOT_EXIST;
  }

  public void set(int x, int y) {
    this.x = x; this.y = y;
    mx = rnd.nextInt()%32;
    my = rnd.nextInt()%32;
    cnt = 32 + Math.abs(rnd.nextInt())%32;
  }

  private final int COLOR = 0xff2222;

  public void move() {
    px = x; py = y;
    x += (mx<<1); y += (my<<1);
    cnt--;
  }

  public void draw() {
    gameManager.screen.drawLine(x>>4, y>>4, px>>4, py>>4, COLOR);
  }
}
