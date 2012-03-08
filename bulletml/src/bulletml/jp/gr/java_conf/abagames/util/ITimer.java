/*
 * $Id: ITimer.java,v 1.1 2001/05/11 15:00:49 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.util;

/**
 * Timer interface.
 *
 * @version $Revision: 1.1 $
 */
public interface ITimer {
  void activate(int duration, boolean priorityf);
  void deactivate();
  void terminate();
  void setDuration(int duration);
}
