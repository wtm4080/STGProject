/*
 * $Id: Screen.java,v 1.4 2001/05/14 14:21:58 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import java.awt.*;
import java.awt.image.*;
import java.applet.Applet;
import java.util.Random;

/**
 * Draw applet screen.
 *
 * @version $Revision: 1.4 $
 */
public class Screen {
  private int pbuf[], bpbuf[];
  private int pbuf1[], pbuf2[];
  private int bufBldIdx[];
  private MemoryImageSource imageSource;
  private Image bufImage;

  private final int SCREEN_HEIGHT = Noiz.SCREEN_HEIGHT;
  private final int SCREEN_WIDTH = Noiz.SCREEN_WIDTH;

  //private Random rnd = new Random();

  public Screen() {
    pbuf1 = new int[Noiz.SCREEN_WIDTH * Noiz.SCREEN_HEIGHT+1];
    pbuf2 = new int[Noiz.SCREEN_WIDTH * Noiz.SCREEN_HEIGHT+1];
    pbuf = pbuf1; bpbuf = pbuf2;

    pbuf1[pbuf1.length-1] = pbuf2[pbuf2.length-1] = 0;
    bufBldIdx = new int[Noiz.SCREEN_WIDTH*Noiz.SCREEN_HEIGHT];
    for ( int i = Noiz.SCREEN_WIDTH*Noiz.SCREEN_HEIGHT-1 ; i>=0 ; i-- ){
      int y = i/Noiz.SCREEN_WIDTH;
      int x = i-y*Noiz.SCREEN_HEIGHT;
      x -= Noiz.SCREEN_WIDTH/2; y -= Noiz.SCREEN_HEIGHT/2;
      //x *= 0.95f; y *= 0.95f;
      //x *= 1.05f; y *= 1.05f;
      //x += (rnd.nextInt()%3);
      //y += (rnd.nextInt()%3);
      x += Math.sin(3.14*0.05*x)/150;
      y += Math.sin(3.14*0.05*y)/150;
      x += Noiz.SCREEN_WIDTH/2; y += Noiz.SCREEN_HEIGHT/2;
      if ( x>=0 && x<Noiz.SCREEN_WIDTH && y>=0 && y<Noiz.SCREEN_HEIGHT ) {
        bufBldIdx[i] = x+y*Noiz.SCREEN_WIDTH;
      } else {
        bufBldIdx[i] = pbuf1.length-1;
      }
    }
  }

  /**
   * make screen buffer(off screen image)
   */
  public void makeBuffer(Component cmp) {
    imageSource = new MemoryImageSource
      (Noiz.SCREEN_WIDTH, Noiz.SCREEN_HEIGHT, pbuf, 0, Noiz.SCREEN_WIDTH);
    imageSource.setAnimated(true);
    bufImage = cmp.createImage(imageSource);
    grp = cmp.getGraphics();
  }

  /**
   * clear screen and make smoke effect
   */
  public final void clear() {
    /*for ( int i=pbuf.length-2 ; i>=0 ; i-- ){
        pbuf[i] = 0xff000000;
    }*/
    System.arraycopy(pbuf, 0, bpbuf, 0, bufBldIdx.length);
    for ( int i=bufBldIdx.length-1 ; i>=0 ; i-- ){
      int px = bpbuf[bufBldIdx[i]];
      int r = (((px&0xff0000)>>8 ) * 200)&0xff0000;
      int g = (((px&0x00ff00)>>8 ) * 160)&0x00ff00;
      int b =  ((px&0x0000ff)    ) * 240 >> 8;
      pbuf[i] = 0xff000000 | r | g | b;
    }
  }

  private ColorModel colorModel = ColorModel.getRGBdefault();
  private Graphics grp;

  public final void swap() {
    imageSource.newPixels();
    grp.drawImage(bufImage, 0, 0, null);
  }

  private final int alphaBlend(int a, int b, int rate) {
    int tmp;
    tmp = (b & 0xff0000)>>16;
    int red = ((((a & 0xff0000)>>16) - tmp) * rate >>16) + tmp;
    tmp = (b & 0x00ff00)>>8;
    int green = ((((a & 0x00ff00)>>8 ) - tmp) * rate >>16) + tmp;
    tmp = (b & 0x0000ff);
    int blue = ((((a & 0x0000ff)    ) - tmp) * rate >>16) + tmp;
    return (red<<16) | (green<<8) | blue | 0xff000000;
  }

  /**
   * draw alpha blended line
   */
  public final void drawLine(int x1, int y1, int x2, int y2, int color) {
    if ( x1 < 0 ) {
      if ( x2 < 0 ) return;
      y1 = (y1-y2)*x2/(x2-x1)+y2;
      x1 = 0;
    } else if ( x2 < 0 ) {
      y2 = (y2-y1)*x1/(x1-x2)+y1;
      x2 = 0;
    }
    if ( x1 > SCREEN_WIDTH-1 ) {
      if ( x2 > SCREEN_WIDTH-1 ) return;
      y1 = (y1-y2)*(x2-(SCREEN_WIDTH-1))/(x2-x1)+y2;
      x1 = SCREEN_WIDTH-1;
    } else if ( x2 > SCREEN_WIDTH-1 ) {
      y2 = (y2-y1)*(x1-(SCREEN_WIDTH-1))/(x1-x2)+y1;
      x2 = SCREEN_HEIGHT-1;
    }
    if ( y1 < 1 ) {
      if ( y2 < 1 ) return;
      x1 = (x1-x2)*(y2-1)/(y2-y1)+x2;
      y1 = 1;
    } else if ( y2 < 1 ) {
      x2 = (x2-x1)*(y1-1)/(y1-y2)+x1;
      y2 = 1;
    }
    if ( y1 > SCREEN_HEIGHT-2 ) {
      if ( y2 > SCREEN_HEIGHT-2 ) return;
      x1 = (x1-x2)*(y2-(SCREEN_HEIGHT-2))/(y2-y1)+x2;
      y1 = SCREEN_HEIGHT-2;
    } else if ( y2 > SCREEN_HEIGHT-2 ) {
      x2 = (x2-x1)*(y1-(SCREEN_HEIGHT-2))/(y1-y2)+x1;
      y2 = SCREEN_HEIGHT-2;
    }

    int lx = Math.abs(x2 - x1);
    int ly = Math.abs(y2 - y1);

    if ( lx < ly ) {
      if ( ly == 0 ) ly++;
      int ax = ((x2 - x1)<<16) / ly;
      int ay = ((y2 - y1)>>16) | 1;
      int x  = x1<<16;
      int y  = y1;
      for ( int i=ly-1 ; i>=0 ; i--, x+=ax, y+=ay ){
        int px = x>>16;
        int p1 = y * Noiz.SCREEN_WIDTH + px;
        //pbuf[p1] = color;
        int p2 = p1 + 1;
        int rx = x & 0xffff;
        pbuf[p1] = alphaBlend(pbuf[p1],color,       rx);
        pbuf[p2] = alphaBlend(pbuf[p2],color,0xffff-rx);
      }
    } else {
      if ( lx == 0 ) lx++;
      int ay = ((y2 - y1)<<16) / lx;
      int ax = ((x2 - x1)>>16) | 1;
      int x  = x1;
      int y  = y1<<16;
      for ( int i=lx-1 ; i>0 ; i--, x+=ax, y+=ay ) {
        int py = y>>16;
        int p1 = py * Noiz.SCREEN_WIDTH + x;
        //pbuf[p1] = color;
        int p2 = p1 + Noiz.SCREEN_WIDTH;
        int ry = y & 0xffff;
        pbuf[p1] = alphaBlend(pbuf[p1],color,       ry);
        pbuf[p2] = alphaBlend(pbuf[p2],color,0xffff-ry);
      }
    }
  }

}
