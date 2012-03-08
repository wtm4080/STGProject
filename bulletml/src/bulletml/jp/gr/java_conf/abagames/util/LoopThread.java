/*
 * $Id: LoopThread.java,v 1.1 2001/05/11 15:00:49 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.util;

/**
 * Timer loop thread.
 *
 * @version $Revision: 1.1 $
 */
public class LoopThread implements Runnable {
  private ITime myITime;
  private Thread myThread;

  private boolean loopf = true;

  public LoopThread(ITime aITime) {
    myITime = aITime;
  }

  public void run() {
    while ( loopf ) {
      myITime.wakeUp();
    }
  }

  public void activate(boolean priorityf) {
    myThread = new Thread(this);
    if ( priorityf ) myThread.setPriority(Thread.NORM_PRIORITY-1);
    myThread.start();
  }

  public void deactivate() {
    loopf = false;
  }

  public void terminate() {
    deactivate();
  }
}
