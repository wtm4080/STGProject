/*
 * $Id: ITime.java,v 1.1 2001/05/11 15:00:49 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.util;

/**
 * Interface for instance started by timer.
 *
 * @version $Revision: 1.1 $
 */
public interface ITime {
  void wakeUp();
  void notifyFrame();
}
