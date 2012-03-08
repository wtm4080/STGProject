/*
 * $Id: Timer.java,v 1.1 2001/05/11 15:00:49 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.util;

/**
 * Timer.
 *
 * @version $Revision: 1.1 $
 */
public class Timer implements Runnable, ITimer {
  private int duration;

  private ITime myITime;
  private Thread myThread;
  private LoopThread loopThread;

  private boolean loopf = true;

  public Timer(ITime aITime) {
    myITime = aITime;
  }

  long nextMills;
  long nw;

  public void run() {
    while ( loopf ) {
      try {
        Thread.sleep(duration);
      } catch (InterruptedException e) {}
      myITime.notifyFrame();
    }
  }

  public void activate(int aDuration, boolean priorityf) {
    duration = aDuration;
    myThread = new Thread(this);
    myThread.start();
    loopThread = new LoopThread(myITime);
    loopThread.activate(priorityf);
  }

  public void deactivate() {
    loopf = false;
    loopThread.deactivate();
  }

  public void terminate() {
    deactivate();
  }

  public final void setDuration(int duration) {
    this.duration = duration;
  }
}

