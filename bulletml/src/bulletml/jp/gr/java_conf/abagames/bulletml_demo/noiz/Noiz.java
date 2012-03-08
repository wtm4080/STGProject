/*
 * $Id: Noiz.java,v 1.5 2001/06/03 00:19:12 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import jp.gr.java_conf.abagames.bulletml_demo.BulletmlUtil;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * Noiz applet main routine.
 *
 * @version $Revision: 1.5 $
 */
public class Noiz extends Applet {

  private Screen screen;
  private GameManager gameManager;

  public void init() {
    try {
      jbInit();
    } catch(Exception e) {
      e.printStackTrace();
    }
    vhChoice.addItem("Vertical");
    vhChoice.addItem("Horizontal");
    //Sample.loadSamples();
    for ( int i=0 ; i<Sample.samples.length ; i++ ) {
      sampleChoice.addItem(Sample.samples[i].name);
    }
    BulletmlNoizUtil.setConsole(consoleArea);
  }

  public static final int SCREEN_WIDTH = 320;
  public static final int SCREEN_HEIGHT = 320;

  private boolean startReady = false;

  private void restartGame() {
    if ( gameManager != null ) {
      gameManager.restart();
      consoleArea.append("** stop **\n");
      startButton.setLabel("Start");
      startStopFlag = true;
      gameManager = null;
      screen = null;
    }
  }

  private boolean firstRepaint = false;

  private void startBullets() {
    restartGame();
    screen = new Screen();
    gameManager = new GameManager();
    gameManager.init(this, screen);
    gameManager.initBullets();
    gameManager.loadBulletML(documentArea.getText(), consoleArea);
    gameManager.setHVStat(vhChoice.getSelectedIndex());
    consoleArea.append("-- start --\n");
    startButton.setLabel("Stop");
    startStopFlag = false;
    firstRepaint = true;
    repaint();
  }

  public void stop() {
    restartGame();
  }

  public void destroy() {
    restartGame();
  }

  public void exceptionOccured(Exception e) {
    try {
      StringWriter strWriter = new StringWriter();
      PrintWriter writer = new PrintWriter(strWriter);
      e.printStackTrace(writer);
      consoleArea.append(strWriter.toString());
      writer.close();
      strWriter.close();
    } catch ( IOException ioe ) {}
    restartGame();
  }

  public void paint(Graphics g) {
    if ( screen != null ) {
      screen.makeBuffer(screenPanel);
      if ( gameManager != null && firstRepaint ) {
        firstRepaint = false;
        gameManager.start();
      }
    }
  }

  public void update(Graphics g) {
    paint(g);
  }


  public boolean handleEvent(Event event) {
    if ( gameManager!=null
     && event.target==screenPanel && event.id==event.MOUSE_MOVE ) {
      gameManager.setMousePos(event.x, event.y);
      return true;
    }
    return false;
  }

  private final int NAME_PANEL_HEIGHT = 32;
  Panel ssPanel = new Panel();
  Panel dsPanel = new Panel();
  Panel settingPanel = new Panel();
  TextArea consoleArea = new TextArea();
  Label consoleName = new Label();
  BorderLayout borderLayout3 = new BorderLayout();
  Panel csPanel = new Panel();
  Panel screenPanel = new Panel();
  GridLayout gridLayout2 = new GridLayout();
  GridLayout gridLayout3 = new GridLayout();
  Panel startPanel = new Panel();
  BorderLayout borderLayout1 = new BorderLayout();
  Button startButton = new Button();
  Panel choicesPanel = new Panel();
  Choice vhChoice = new Choice();
  GridLayout gridLayout1 = new GridLayout();
  BorderLayout borderLayout2 = new BorderLayout();
  Panel docPanel = new Panel();
  Panel samplePanel = new Panel();
  TextArea documentArea = new TextArea();
  Label documentName = new Label();
  BorderLayout borderLayout4 = new BorderLayout();
  Choice sampleChoice = new Choice();
  BorderLayout borderLayout5 = new BorderLayout();
  BorderLayout borderLayout6 = new BorderLayout();

  private void jbInit() throws Exception {
    this.setLayout(gridLayout2);
    dsPanel.setLayout(borderLayout4);
    settingPanel.setLayout(borderLayout1);
    consoleArea.setEditable(false);
    consoleArea.setFont(new java.awt.Font("Monospaced", 0, 9));
    consoleName.setText("Console");
    csPanel.setLayout(borderLayout3);
    screenPanel.setLayout(null);
    ssPanel.setLayout(gridLayout3);
    gridLayout3.setRows(2);
    gridLayout3.setColumns(1);
    gridLayout2.setColumns(2);
    startButton.setLabel("Start");
    startButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        startButton_actionPerformed(e);
      }
    });
    choicesPanel.setLayout(gridLayout1);
    startPanel.setLayout(borderLayout2);
    documentArea.setFont(new java.awt.Font("Monospaced", 0, 11));
    documentName.setText("Document");
    docPanel.setLayout(borderLayout5);
    samplePanel.setLayout(borderLayout6);
    sampleChoice.addItemListener(new java.awt.event.ItemListener() {
      public void itemStateChanged(ItemEvent e) {
        sampleChoice_itemStateChanged(e);
      }
    });
    rankBar.setOrientation(0);
    rankBar.setValue(50);
    rankBar.addAdjustmentListener(new java.awt.event.AdjustmentListener() {
      public void adjustmentValueChanged(AdjustmentEvent e) {
        rankBar_adjustmentValueChanged(e);
      }
    });
    rankEasy.setAlignment(1);
    rankEasy.setText("Easy");
    rankHard.setAlignment(1);
    rankHard.setText("Hard");
    rankPanel.setLayout(borderLayout7);
    this.add(ssPanel, null);
    ssPanel.add(screenPanel, null);
    ssPanel.add(settingPanel, null);
    settingPanel.add(startPanel, BorderLayout.NORTH);
    startPanel.add(startButton, BorderLayout.NORTH);
    startPanel.add(choicesPanel, BorderLayout.CENTER);
    choicesPanel.add(vhChoice, null);
    startPanel.add(rankPanel, BorderLayout.SOUTH);
    rankPanel.add(rankEasy, BorderLayout.WEST);
    rankPanel.add(rankBar, BorderLayout.CENTER);
    rankPanel.add(rankHard, BorderLayout.EAST);
    settingPanel.add(csPanel, BorderLayout.CENTER);
    csPanel.add(consoleArea, BorderLayout.CENTER);
    csPanel.add(consoleName, BorderLayout.NORTH);
    this.add(dsPanel, null);
    dsPanel.add(docPanel, BorderLayout.CENTER);
    docPanel.add(documentName, BorderLayout.NORTH);
    docPanel.add(documentArea, BorderLayout.CENTER);
    dsPanel.add(samplePanel, BorderLayout.NORTH);
    samplePanel.add(sampleChoice, BorderLayout.CENTER);
  }

  private boolean startStopFlag = true;
  Panel rankPanel = new Panel();
  Scrollbar rankBar = new Scrollbar();
  Label rankEasy = new Label();
  Label rankHard = new Label();
  BorderLayout borderLayout7 = new BorderLayout();

  void startButton_actionPerformed(ActionEvent e) {
    if ( startStopFlag ) {
      startBullets();
    } else {
      restartGame();
    }
  }

  void sampleChoice_itemStateChanged(ItemEvent e) {
    Sample sml = Sample.samples[sampleChoice.getSelectedIndex()];
    /*if ( sml.name.startsWith("V") ) {
      vhChoice.select(0);
    } else if ( sml.name.startsWith("H") ) {
      vhChoice.select(1);
    }*/
    documentArea.setText(sml.context);
  }

  void rankBar_adjustmentValueChanged(AdjustmentEvent e) {
    BulletmlUtil.setRank((float)rankBar.getValue()/100);
  }

  public void selectVrtHrz(int idx) {
    vhChoice.select(idx);
  }

  public static void main(String[] args) {
    Noiz noiz = new Noiz();
    Frame frame;
    frame = new Frame() {
      protected void processWindowEvent(WindowEvent e) {
        super.processWindowEvent(e);
        if (e.getID() == WindowEvent.WINDOW_CLOSING) {
          System.exit(0);
        }
      }
      public synchronized void setTitle(String title) {
        super.setTitle(title);
        enableEvents(AWTEvent.WINDOW_EVENT_MASK);
      }
    };
    frame.setTitle("BulletML Demo");
    frame.add(noiz, BorderLayout.CENTER);
    noiz.init();
    noiz.start();
    frame.setSize(640, 640);
    Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
    frame.setLocation((d.width - frame.getSize().width) / 2, (d.height - frame.getSize().height) / 2);
    frame.setVisible(true);
  }
}
