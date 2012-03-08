package jp.gr.java_conf.abagames.bulletml;

/**
 * @version bulletml.rlx 1.0 (Sun Jun 03 09:44:35 JST 2001)
 * @author  Relaxer 0.13 (http://www.relaxer.org)
 */
public interface IRNode {
    /**
     * Sets parent RNode.
     *
     * @param parent
     */
    void setParentRNode(IRNode parent);

    /**
     * Gets parent RNode.
     *
     * @return IRNode
     */
    IRNode getParentRNode();

    /**
     * Gets child RNodes.
     *
     * @return IRNode[]
     */
    IRNode[] getRNodes();
}
