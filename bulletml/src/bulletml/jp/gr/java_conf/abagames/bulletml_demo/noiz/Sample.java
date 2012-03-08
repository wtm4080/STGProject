/*
 * $Id: Sample.java,v 1.4 2001/06/03 00:50:45 ChoK Exp $
 *
 * Copyright 2001 Kenta Cho. All rights reserved.
 */
package jp.gr.java_conf.abagames.bulletml_demo.noiz;

import java.io.*;

/**
 * BulletML samples.
 *
 * @version $Revision: 1.4 $
 */
public class Sample {

public final static Sample[] samples = {
new Sample(
"template.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml \n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n\n</bulletml>\n"
),
new Sample(
"[1943]_rolling_fire.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<fire>\n<bulletRef label=\"roll\"/>\n</fire>\n</action>\n\n<bullet label=\"roll\">\n<action>\n<wait>40+$rand*20</wait>\n<changeDirection>\n <direction type=\"relative\">-90</direction>\n <term>4</term>\n</changeDirection>\n<changeSpeed>\n <speed>3</speed>\n <term>4</term>\n</changeSpeed>\n<wait>4</wait>\n<changeDirection>\n <direction type=\"sequence\">15</direction>\n <term>9999</term>\n</changeDirection>\n<wait>80+$rand*40</wait>\n<vanish/>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[G_DARIUS]_homing_laser.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>8</times>\n<action>\n <fire>\n  <direction>-60+$rand*120</direction>\n  <bulletRef label=\"hmgLsr\"/>\n </fire>\n <repeat><times>8</times>\n <action>\n  <wait>1</wait>\n  <fire>\n   <direction type=\"sequence\">0</direction>\n   <bulletRef label=\"hmgLsr\"/>\n  </fire>\n </action>\n </repeat>\n <wait>10</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"hmgLsr\">\n<speed>2</speed>\n<action>\n<changeSpeed>\n <speed>0.3</speed>\n <term>30</term>\n</changeSpeed>\n<wait>100</wait>\n<changeSpeed>\n <speed>5</speed>\n <term>100</term>\n</changeSpeed>\n</action>\n<action>\n<repeat><times>9999</times>\n<action>\n <changeDirection>\n  <direction type=\"aim\">0</direction>\n  <term>60-$rank*20</term>\n </changeDirection>\n <wait>5</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Guwange]_round_2_boss_circle_fire.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<fire label=\"circle\">\n<direction type=\"sequence\">$1</direction>\n<speed>6</speed>\n<bullet>\n<action>\n <wait>3</wait>\n <fire>\n  <direction type=\"absolute\">$2</direction>\n  <speed>1.5+$rank</speed>\n  <bullet/>\n </fire>\n <vanish/>\n</action>\n</bullet>\n</fire>\n\n<action label=\"fireCircle\">\n<repeat> <times>18</times>\n<action>\n<fireRef label=\"circle\">\n <param>20</param>\n <param>$1</param>\n</fireRef>\n</action>\n</repeat>\n</action>\n\n<action label=\"top\">\n<actionRef label=\"fireCircle\">\n <param>180-45+90*$rand</param>\n</actionRef>\n</action>\n\n</bulletml>\n"
),
new Sample(
"[Guwange]_round_3_boss_fast_3way.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat> <times>6+$rank*8</times>\n<action>\n<fire>\n <direction>$rand*360</direction>\n <speed>5</speed>\n <bulletRef label=\"seed\">\n  <param>5+$rand*10</param>\n </bulletRef>\n</fire>\n<wait>20</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"seed\">\n<action>\n<changeSpeed>\n <speed>0</speed>\n <term>$1</term>\n</changeSpeed>\n<wait>$1</wait>\n<fire>\n <direction type=\"aim\">-20</direction>\n <bulletRef label=\"3way\"/>\n</fire>\n<repeat> <times>2</times>\n<action>\n <fire>\n  <direction type=\"sequence\">20</direction>\n  <bulletRef label=\"3way\"/>\n </fire>\n</action>\n</repeat>\n<wait>1</wait>\n<repeat> <times>2</times>\n<action>\n <fire>\n  <direction type=\"sequence\">0</direction>\n  <speed type=\"sequence\">-0.1</speed>\n  <bulletRef label=\"3way\"/>\n </fire>\n <repeat> <times>2</times>\n <action>\n  <fire>\n   <direction type=\"sequence\">-20</direction>\n   <speed type=\"sequence\">0</speed>\n   <bulletRef label=\"3way\"/>\n  </fire>\n </action>\n </repeat>\n <wait>1</wait>\n <fire>\n  <direction type=\"sequence\">0</direction>\n  <speed type=\"sequence\">-0.1</speed>\n  <bulletRef label=\"3way\"/>\n </fire>\n <repeat> <times>2</times>\n <action>\n  <fire>\n   <direction type=\"sequence\">20</direction>\n   <speed type=\"sequence\">0</speed>\n   <bulletRef label=\"3way\"/>\n  </fire>\n </action>\n </repeat>\n <wait>1</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n<bullet label=\"3way\">\n<speed>1.8</speed>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Guwange]_round_4_boss_eye_ball.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat> <times>4+$rank*4</times>\n<action>\n <fire>\n  <direction>$rand*360</direction>\n  <bulletRef label=\"eye\"/>\n </fire>\n <wait>30</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"eye\">\n<speed>0</speed>\n<action>\n<changeSpeed>\n <speed>10</speed>\n <term>400</term>\n</changeSpeed>\n<changeDirection>\n <direction type=\"sequence\">$rand*5-2</direction>\n <term>9999</term>\n</changeDirection>\n<repeat> <times>9999</times>\n<action>\n <fire>\n  <direction type=\"relative\">0</direction>\n  <bulletRef label=\"shadow\"/>\n </fire>\n <wait>4</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n<bullet label=\"shadow\">\n<speed>0</speed>\n<action>\n<wait>20</wait>\n<fire>\n <direction type=\"relative\">90</direction>\n <speed>0.6</speed>\n <bullet/>\n</fire>\n<fire>\n <direction type=\"relative\">-90</direction>\n <speed>0.6</speed>\n <bullet/>\n</fire>\n<vanish/>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_1_boss_grow_bullets.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<fire>\n <direction type=\"absolute\">270-(4+$rank*6)*15/2</direction>\n <bulletRef label=\"seed\"/>\n</fire>\n<repeat><times>4+$rank*6</times>\n<action>\n <fire>\n  <direction type=\"sequence\">15</direction>\n  <bulletRef label=\"seed\"/>\n </fire>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"seed\">\n<speed>1.2</speed>\n<action>\n<changeSpeed>\n <speed>0</speed>\n <term>60</term>\n</changeSpeed>\n<wait>60</wait>\n<fire>\n <speed>0.75</speed>\n <bullet/>\n</fire>\n<repeat><times>4+$rank*4</times>\n<action>\n <fire>\n  <speed type=\"sequence\">0.15</speed>\n  <bullet/>\n </fire>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_2_boss_struggling.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat> <times>100</times>\n<action>\n <fire>\n  <direction type=\"sequence\">180</direction>\n  <bulletRef label=\"changeStraight\"/>\n </fire>\n <fire>\n  <direction type=\"sequence\">160</direction>\n  <bulletRef label=\"changeStraight\"/>\n </fire>\n <wait>2</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"changeStraight\">\n<speed>0.6</speed>\n<action>\n<wait>20+$rand*100</wait>\n<changeDirection>\n <direction type=\"absolute\">270</direction>\n <term>60</term>\n</changeDirection>\n<changeSpeed>\n <speed>0</speed>\n <term>40</term>\n</changeSpeed>\n<wait>40</wait>\n<changeSpeed>\n <speed>0.5+$rand*0.7</speed>\n <term>20</term>\n</changeSpeed>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_3_boss_back_burst.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat> <times>100</times>\n<action>\n <fire>\n  <direction type=\"absolute\">220+$rand*100</direction>\n  <bulletRef label=\"backBurst\"/>\n </fire>\n <wait>6-$rank*2</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"backBurst\">\n<speed>1.2</speed>\n<action>\n<changeSpeed>\n <speed>0</speed>\n <term>80</term>\n</changeSpeed>\n<wait>60+$rand*20</wait>\n<repeat> <times>2</times>\n<action>\n <fire>\n <direction type=\"absolute\">50+$rand*80</direction>\n <bulletRef label=\"downAccel\"/>\n </fire>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n<bullet label=\"downAccel\">\n<speed>1.8</speed>\n<action>\n<accel>\n <horizontal>-7</horizontal>\n <term>250</term>\n</accel>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_3_boss_wave_bullets.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>32</times>\n<action>\n <fire>\n  <direction type=\"absolute\">320</direction>\n  <bulletRef label=\"wave\">\n   <param>-3</param>\n  </bulletRef>\n </fire>\n <wait>30</wait>\n <fire>\n  <direction type=\"absolute\">220</direction>\n  <bulletRef label=\"wave\">\n   <param>3</param>\n  </bulletRef>\n </fire>\n <wait>30</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"wave\">\n<speed>1</speed>\n<action>\n<fire>\n <direction>0</direction>\n <bulletRef label=\"nrm\"/>\n</fire>\n<repeat><times>8+$rank*10</times>\n<action>\n <fire>\n  <direction type=\"sequence\">$1</direction>\n  <bulletRef label=\"nrm\"/>\n </fire>\n <wait>3</wait>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n<bullet label=\"nrm\">\n<speed>1</speed>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_4_boss_fast_rocket.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"fireRoot\">\n<fire>\n <direction type=\"absolute\">$1</direction>\n <speed>0.2</speed>\n <bulletRef label=\"rootBl\"/>\n</fire>\n<repeat> <times>3</times>\n<action>\n<fire>\n <direction type=\"absolute\">$1</direction>\n <speed type=\"sequence\">0.4</speed>\n <bulletRef label=\"rootBl\"/>\n</fire>\n</action>\n</repeat>\n</action>\n\n<action label=\"top\">\n<actionRef label=\"fireRoot\">\n <param>$rand*16</param>\n</actionRef>\n<actionRef label=\"fireRoot\">\n <param>180+$rand*16</param>\n</actionRef>\n<wait>120</wait>\n</action>\n\n<bullet label=\"rootBl\">\n<action>\n<wait>40</wait>\n<fire>\n <direction type=\"absolute\">274+$rand*4</direction>\n <bulletRef label=\"rocket\"/>\n</fire>\n<vanish/>\n</action>\n</bullet>\n\n<bullet label=\"rocket\">\n<speed>5+$rand</speed>\n<action>\n<repeat> <times>9999</times>\n <action>\n <fire>\n  <direction type=\"absolute\">0</direction>\n  <speed>1</speed>\n  <bulletRef label=\"downAccel\"/>\n </fire>\n <fire>\n  <direction type=\"absolute\">60</direction>\n  <speed>1.8</speed>\n  <bulletRef label=\"downAccel\"/>\n </fire>\n <wait>3</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n<bullet label=\"downAccel\">\n<action>\n<accel>\n<vertical>2.7</vertical>\n<term>120</term>\n</accel>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_5_boss_last_round_wave.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>2+$rank*1.5</times>\n<action>\n <fire>\n  <bulletRef label=\"rfRkt\"/>\n </fire>\n <wait>45</wait>\n</action>\n</repeat>\n<wait>60</wait>\n</action>\n\n<bullet label=\"rfRkt\">\n<action>\n<repeat><times>9999</times>\n<action>\n <wait>1</wait>\n <fire>\n  <direction type=\"sequence\">13</direction>\n  <bullet/>\n </fire>\n</action>\n</repeat>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_5_middle_boss_rockets.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>50</times>\n<action>\n <fire>\n  <direction type=\"absolute\">270</direction>\n  <bulletRef label=\"rocket\"/>\n </fire>\n <wait>10</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"rocket\">\n<action>\n<repeat><times>9999</times>\n<action>\n <fireRef label=\"udBlt\">\n  <param>90</param>\n </fireRef>\n <wait>20-$rank*8</wait>\n <fireRef label=\"udBlt\">\n  <param>-90</param>\n </fireRef>\n <wait>20-$rank*8</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n<fire label=\"udBlt\">\n<direction type=\"relative\">$1-25+$rand*50</direction>\n<bullet/>\n</fire>\n\n</bulletml>\n"
),
new Sample(
"[Progear]_round_6_boss_parabola_shot.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>50</times>\n<action>\n <fire>\n  <direction type=\"absolute\">190+$rand*30</direction>\n  <bulletRef label=\"seed\"/>\n </fire>\n <wait>15-$rank*5</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"seed\">\n<speed>1</speed>\n<action>\n<changeSpeed>\n <speed>0</speed>\n <term>60</term>\n</changeSpeed>\n<wait>60</wait>\n<fire><bullet/></fire>\n<fire>\n <direction type=\"absolute\">330+$rand*25</direction>\n <bulletRef label=\"downAccel\"/>\n</fire>\n<repeat> <times>3</times>\n<action>\n <fire>\n  <direction type=\"sequence\">0</direction>\n  <speed type=\"sequence\">-0.4</speed>\n  <bulletRef label=\"downAccel\"/>\n </fire>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n<bullet label=\"downAccel\">\n<speed>2</speed>\n<action>\n<accel>\n <vertical>3</vertical>\n <term>120</term>\n</accel>\n</action>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[Psyvariar]_X-A_boss_opening.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat> <times>100</times>\n<action>\n <fire>\n  <direction>-45+$rand*90</direction>\n  <speed>0.4+$rand*0.8</speed>\n  <bullet/>\n </fire>\n <wait>2</wait>\n</action>\n</repeat>\n</action>\n\n</bulletml>\n"
),
new Sample(
"[Psyvariar]_X-A_boss_winder.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<bullet label=\"winderBullet\">\n <speed>3</speed>\n</bullet>\n\n<fire label=\"fireWinder\">\n <direction type=\"sequence\">$1</direction>\n <bulletRef label=\"winderBullet\"/>\n</fire>\n\n<action label=\"roundWinder\">\n <fireRef label=\"fireWinder\">\n  <param>$1</param>\n </fireRef>\n <repeat> <times>11</times>\n <action>\n  <fireRef label=\"fireWinder\">\n   <param>30</param>\n  </fireRef>\n </action>\n </repeat>\n <wait>5</wait>\n</action>\n\n<action label=\"winderSequence\">\n<repeat> <times>12</times>\n<actionRef label=\"roundWinder\">\n <param>30</param>\n</actionRef>\n</repeat>\n<repeat> <times>12</times>\n<actionRef label=\"roundWinder\">\n <param>$1</param>\n</actionRef>\n</repeat>\n<repeat> <times>12</times>\n<actionRef label=\"roundWinder\">\n <param>30</param>\n</actionRef>\n</repeat>\n</action>\n\n<action label=\"top1\">\n<fire>\n <direction type=\"absolute\">2</direction>\n <bulletRef label=\"winderBullet\"/>\n</fire>\n<actionRef label=\"winderSequence\">\n <param>31</param>\n</actionRef>\n</action>\n\n\n<action label=\"top2\">\n<fire>\n <direction type=\"absolute\">-2</direction>\n <bulletRef label=\"winderBullet\"/>\n</fire>\n<actionRef label=\"winderSequence\">\n <param>29</param>\n</actionRef>\n</action>\n\n</bulletml>\n"
),
new Sample(
"[Psyvariar]_X-B_colony_shape_satellite.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<repeat><times>5</times>\n<action>\n <fire>\n  <direction type=\"absolute\">152</direction>\n  <bulletRef label=\"norm\"/>\n </fire>\n <repeat><times>8</times>\n <action>\n  <fire>\n   <direction type=\"sequence\">7</direction>\n   <bulletRef label=\"norm\"/>\n  </fire>\n </action>\n </repeat>\n <wait>8</wait>\n</action>\n</repeat>\n<wait>10</wait>\n<repeat><times>7</times>\n<action>\n <fire>\n  <direction type=\"absolute\">180-45+$rand*90</direction>\n  <bulletRef label=\"norm\"/>\n </fire>\n <repeat><times>4</times>\n <action>\n  <fire>\n   <direction type=\"sequence\">0</direction>\n   <speed>1.5</speed>\n   <bulletRef label=\"norm\"/>\n  </fire>\n  <wait>4</wait>\n </action>\n </repeat>\n</action>\n</repeat>\n<wait>10</wait>\n<repeat><times>12</times>\n<action>\n <fire>\n  <direction>0</direction>\n  <speed>2</speed>\n  <bulletRef label=\"norm\"/>\n </fire>\n <wait>6</wait>\n</action>\n</repeat>\n</action>\n\n<bullet label=\"norm\">\n<speed>1</speed>\n</bullet>\n\n</bulletml>\n"
),
new Sample(
"[XEVIOUS]_garu_zakato.xml",
"<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml type=\"vertical\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"top\">\n<fire>\n <direction type=\"absolute\">180</direction>\n <speed>3</speed>\n <bulletRef label=\"gzc\"/>\n</fire>\n</action>\n\n<bullet label=\"gzc\">\n<action>\n<wait>10+$rand*10</wait>\n<repeat><times>16</times>\n<action>\n <fire>\n  <direction type=\"sequence\">360/16</direction>\n  <bulletRef label=\"spr\"/>\n </fire>\n</action>\n</repeat>\n<repeat><times>4</times>\n<action>\n <fire>\n  <direction type=\"sequence\">90</direction>\n  <bulletRef label=\"hrmSpr\"/>\n </fire>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n<bullet label=\"spr\">\n<speed>2</speed>\n</bullet>\n\n<bullet label=\"hrmSpr\">\n<speed>0</speed>\n<action>\n<changeSpeed>\n <speed>2</speed>\n <term>60</term>\n</changeSpeed>\n</action>\n<action>\n<repeat><times>9999</times>\n<action>\n <changeDirection>\n  <direction type=\"aim\">0</direction>\n  <term>40</term>\n </changeDirection>\n <wait>1</wait>\n</action>\n</repeat>\n</action>\n</bullet>\n\n</bulletml>\n"
),
};

  public String name;
  public String context;

  public Sample(String name, String context) {
    this.name = name;
    this.context = context;
  }

  /*public Sample(String name, String context) {
    this.name = name;
    int dtdIdx = context.indexOf(DTD_URL);
    if ( dtdIdx != -1 ) {
      StringBuffer cnt = new StringBuffer();
      cnt.append(context.substring(0, dtdIdx));
      cnt.append(DTD_FILE_URL);
      cnt.append(context.substring(dtdIdx+DTD_URL.length()));
      this.context = cnt.toString();
    } else {
      this.context = context;
    }
  }

  private static final String DTD_URL
   = "http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd";
  private static final String DTD_FILE_URL
   = "file:///d:\\bulletml\\bulletml.dtd";

  public static Sample[] samples;

  public Sample() {}

  private static final String SAMPLE_DIRECTORY = "sample";

  public static void loadSamples() {
    File file = new File(SAMPLE_DIRECTORY);
    String[] sampleFiles = file.list();
    samples = new Sample[sampleFiles.length+1];
    samples[0] = new Sample();
    samples[0].name = "template";
    samples[0].context = "<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/bulletml.dtd\">\n\n<bulletml xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n\n</bulletml>";
    for ( int i=0 ; i<sampleFiles.length ; i++ ) {
      samples[i+1] = new Sample();
      samples[i+1].name = sampleFiles[i];
      try {
        BufferedReader reader = new BufferedReader(
         new FileReader(SAMPLE_DIRECTORY + File.separator + sampleFiles[i]));
        StringBuffer cnt = new StringBuffer();
        for ( ; ; ) {
          String line = reader.readLine();
          if ( line == null ) break;
          int dtdIdx = line.indexOf(DTD_URL);
          if ( dtdIdx != -1 ) {
            cnt.append(line.substring(0, dtdIdx));
            cnt.append(DTD_FILE_URL);
            cnt.append(line.substring(dtdIdx+DTD_URL.length()));
          } else {
            cnt.append(line);
          }
          cnt.append("\n");
        }
        samples[i+1].context = cnt.toString();
      } catch ( FileNotFoundException e ) {
        e.printStackTrace();
      } catch ( IOException e ) {
        e.printStackTrace();
      }
    }
  }*/
}
