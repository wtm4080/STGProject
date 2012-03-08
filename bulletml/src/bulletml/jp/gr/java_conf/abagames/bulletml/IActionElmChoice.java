package jp.gr.java_conf.abagames.bulletml;

import java.io.*;
import java.net.URL;
import java.net.MalformedURLException;
import org.xml.sax.*;
import org.w3c.dom.*;

/**
 * <b>IActionElmChoice</b> is generated by Relaxer based on bulletml.rlx.
 *
 * @version bulletml.rlx 0.21 (Sun Jun 03 09:44:34 JST 2001)
 * @author  Relaxer 0.13 (http://www.relaxer.org)
 */
public interface IActionElmChoice extends IRNode {
    /**
     * Creates a DOM representation of the object.
     * Result is appended to the Node <code>parent</code>.
     *
     * @param parent
     */
    void makeElement(Node parent);

    /**
     * Makes a XML text representation.
     *
     * @param buffer
     */
    void makeTextElement(StringBuffer buffer);

    /**
     * Makes a XML text representation.
     *
     * @param buffer
     */
    void makeTextElement(PrintWriter buffer);
}
