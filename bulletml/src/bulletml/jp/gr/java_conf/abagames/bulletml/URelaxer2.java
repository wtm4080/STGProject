package jp.gr.java_conf.abagames.bulletml;

import java.util.*;
import java.io.File;
import java.io.IOException;
import java.net.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.io.ByteArrayOutputStream;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.text.DateFormat;
import java.text.ParseException;
import org.w3c.dom.*;

/**
 * URelaxer2
 * This class can be executed on the DOM2 parser.
 *
 * @since   Sep.  3, 2000
 * @version Jan. 18, 2001
 * @author  ASAMI, Tomoharu (asami@zeomtech.com)
 */
public final class URelaxer2 {
    // String type
    public static String getElementPropertyAsString(
	Element element
    ) {
	return (element2Text(element));
    }

    public static String getElementPropertyAsString(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Text(property);
	return (text);
    }

    public static List getElementPropertyAsStringList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(element2Text(nodes[i]));
	}
	return (list);
    }

    public static String getElementPropertyAsStringByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (element2Text(property));
    }

    public static List getElementPropertyAsStringListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(element2Text(property));
	}
	return (list);
    }

    public static String getAttributePropertyAsString(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (value);
	}
    }

    public static List getAttributePropertyAsStringList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	String value = getAttribute(element, namespaceURI, localName);
	if (value != null) {
	    StringTokenizer st = new StringTokenizer(value);
	    while (st.hasMoreTokens()) {
		list.add(st.nextToken());
	    }
	}
	return (list);
    }

    public static void setElementPropertyByString(
	Element element,
	String namespaceURI,
	String localName,
	String value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value);
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByString(
	Element element,
	String value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(value);
	element.appendChild(text);
    }

    public static void setElementPropertyByStringList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setAttributePropertyByString(
	Element element,
	String namespaceURI,
	String localName,
	String value,
	RNSContext nsContext
    ) {
	if (value == null || "".equals(value)) { // by horst.fiedler@tifff.com
	    if (getAttribute(element, namespaceURI, localName) != null) {
		element.removeAttributeNS(namespaceURI, localName);
	    }
	} else {
	    element.setAttributeNS(namespaceURI, localName, value);
	}
    }

    public static void setAttributePropertyByStringList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	StringBuffer buffer = new StringBuffer();
	int size = values.size();
	if (size > 0) {
	    buffer.append(values.get(0).toString());
	    for (int i = 1;i < size;i++) {
		buffer.append(" ");
		buffer.append(values.get(i).toString());
	    }
	}
	element.setAttributeNS(namespaceURI, localName, new String(buffer));
    }

    // boolean type
    public static boolean getElementPropertyAsBoolean(
	Element element
    ) {
	String text = element2Data(element);
	if ("true".equals(text)) {
	    return (true);
	} else if ("false".equals(text)) {
	    return (false);
	} else if ("1".equals(text)) {
	    return (true);
	} else if ("0".equals(text)) {
	    return (false);
	} else {
	    throw (new IllegalArgumentException());
	}
    }

    public static boolean getElementPropertyAsBoolean(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	return (getElementPropertyAsBoolean(property));
    }

    public static List getElementPropertyAsBooleanList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Boolean(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Boolean getElementPropertyAsBooleanByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Boolean(element2Data(property)));
    }

    public static List getElementPropertyAsBooleanListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Boolean(element2Text(property)));
	}
	return (list);
    }

    public static boolean getAttributePropertyAsBoolean(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if ("true".equals(value)) {
	    return (true);
	} else if ("false".equals(value)) {
	    return (false);
	} else {
	    return (false);
	}
    }

    public static Boolean getAttributePropertyAsBooleanObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if ("true".equals(value)) {
	    return (Boolean.TRUE);
	} else if ("false".equals(value)) {
	    return (Boolean.FALSE);
	} else {
	    return (null);
	}
    }

    public static void setElementPropertyByBoolean(
	Element element,
	String namespaceURI,
	String localName,
	boolean value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(new Boolean(value).toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByBoolean(
	Element element,
	String namespaceURI,
	String localName,
	Boolean value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByBooleanList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByBoolean(
	Element element,
	boolean value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(new Boolean(value).toString());
	element.appendChild(text);
    }

    public static void setAttributePropertyByBoolean(
	Element element,
	String namespaceURI,
	String localName,
	boolean value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, new Boolean(value).toString());
    }

    public static void setAttributePropertyByBoolean(
	Element element,
	String namespaceURI,
	String localName,
	Boolean value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // byte type
    public static byte getElementPropertyAsByte(
	Element element
    ) {
	String text = element2Data(element);
	return (Byte.parseByte(text));
    }

    public static byte getElementPropertyAsByte(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Byte.parseByte(text));
    }

    public static List getElementPropertyAsByteList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Byte(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Byte getElementPropertyAsByteByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Byte(element2Data(property)));
    }

    public static List getElementPropertyAsByteListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Byte(element2Text(property)));
	}
	return (list);
    }

    public static byte getAttributePropertyAsByte(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Byte.parseByte(value));
	}
    }

    public static Byte getAttributePropertyAsByteObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Byte(value));
	}
    }

    public static void setElementPropertyByByte(
	Element element,
	String namespaceURI,
	String localName,
	byte value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Byte.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByByte(
	Element element,
	String namespaceURI,
	String localName,
	Byte value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByByteList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByByte(
	Element element,
	byte value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Byte.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByByte(
	Element element,
	String namespaceURI,
	String localName,
	byte value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Byte.toString(value));
    }

    public static void setAttributePropertyByByte(
	Element element,
	String namespaceURI,
	String localName,
	Byte value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // short type
    public static short getElementPropertyAsShort(
	Element element
    ) {
	String text = element2Data(element);
	return (Short.parseShort(text));
    }

    public static short getElementPropertyAsShort(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Short.parseShort(text));
    }

    public static List getElementPropertyAsShortList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Short(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Short getElementPropertyAsShortByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Short(element2Data(property)));
    }

    public static List getElementPropertyAsShortListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Short(element2Text(property)));
	}
	return (list);
    }

    public static short getAttributePropertyAsShort(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Short.parseShort(value));
	}
    }

    public static Short getAttributePropertyAsShortObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Short(value));
	}
    }

    public static void setElementPropertyByShort(
	Element element,
	String namespaceURI,
	String localName,
	short value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Short.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByShort(
	Element element,
	String namespaceURI,
	String localName,
	Short value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByShortList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByShort(
	Element element,
	short value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Short.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByShort(
	Element element,
	String namespaceURI,
	String localName,
	short value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Short.toString(value));
    }

    public static void setAttributePropertyByShort(
	Element element,
	String namespaceURI,
	String localName,
	Short value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // int type
    public static int getElementPropertyAsInt(
	Element element
    ) {
	String text = element2Data(element);
	return (Integer.parseInt(text));
    }

    public static int getElementPropertyAsInt(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Integer.parseInt(text));
    }

    public static List getElementPropertyAsIntList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Integer(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Integer getElementPropertyAsIntByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Integer(element2Data(property)));
    }

    public static List getElementPropertyAsIntListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Integer(element2Text(property)));
	}
	return (list);
    }

    public static int getAttributePropertyAsInt(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Integer.parseInt(value));
	}
    }

    public static Integer getAttributePropertyAsIntObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Integer(value));
	}
    }

    public static void setElementPropertyByInt(
	Element element,
	String namespaceURI,
	String localName,
	int value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Integer.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByInt(
	Element element,
	String namespaceURI,
	String localName,
	Integer value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByIntList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByInt(
	Element element,
	int value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Integer.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByInt(
	Element element,
	String namespaceURI,
	String localName,
	int value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Integer.toString(value));
    }

    public static void setAttributePropertyByInt(
	Element element,
	String namespaceURI,
	String localName,
	Integer value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // long type
    public static long getElementPropertyAsLong(
	Element element
    ) {
	String text = element2Data(element);
	return (Long.parseLong(text));
    }

    public static long getElementPropertyAsLong(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Long.parseLong(text));
    }

    public static List getElementPropertyAsLongList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Long(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Long getElementPropertyAsLongByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Long(element2Data(property)));
    }

    public static List getElementPropertyAsLongListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Long(element2Text(property)));
	}
	return (list);
    }

    public static long getAttributePropertyAsLong(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Long.parseLong(value));
	}
    }

    public static Long getAttributePropertyAsLongObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Long(value));
	}
    }

    public static void setElementPropertyByLong(
	Element element,
	String namespaceURI,
	String localName,
	long value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Long.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByLong(
	Element element,
	String namespaceURI,
	String localName,
	Long value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByLongList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByLong(
	Element element,
	long value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Long.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByLong(
	Element element,
	String namespaceURI,
	String localName,
	long value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Long.toString(value));
    }

    public static void setAttributePropertyByLong(
	Element element,
	String namespaceURI,
	String localName,
	Long value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // float type
    public static float getElementPropertyAsFloat(
	Element element
    ) {
	String text = element2Data(element);
	return (Float.parseFloat(text));
    }

    public static float getElementPropertyAsFloat(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Float.parseFloat(text));
    }

    public static List getElementPropertyAsFloatList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Float(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Float getElementPropertyAsFloatByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Float(element2Data(property)));
    }

    public static List getElementPropertyAsFloatListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Float(element2Text(property)));
	}
	return (list);
    }

    public static float getAttributePropertyAsFloat(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Float.parseFloat(value));
	}
    }

    public static Float getAttributePropertyAsFloatObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Float(value));
	}
    }

    public static void setElementPropertyByFloat(
	Element element,
	String namespaceURI,
	String localName,
	float value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Float.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByFloat(
	Element element,
	String namespaceURI,
	String localName,
	Float value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByFloatList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByFloat(
	Element element,
	float value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Float.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByFloat(
	Element element,
	String namespaceURI,
	String localName,
	float value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Float.toString(value));
    }

    public static void setAttributePropertyByFloat(
	Element element,
	String namespaceURI,
	String localName,
	Float value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // double type
    public static double getElementPropertyAsDouble(
	Element element
    ) {
	String text = element2Data(element);
	return (Double.parseDouble(text));
    }

    public static double getElementPropertyAsDouble(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (Double.parseDouble(text));
    }

    public static List getElementPropertyAsDoubleList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new Double(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Double getElementPropertyAsDoubleByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (new Double(element2Data(property)));
    }

    public static List getElementPropertyAsDoubleListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new Double(element2Text(property)));
	}
	return (list);
    }

    public static double getAttributePropertyAsDouble(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (0);
	} else {
	    return (Double.parseDouble(value));
	}
    }

    public static Double getAttributePropertyAsDoubleObject(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new Double(value));
	}
    }

    public static void setElementPropertyByDouble(
	Element element,
	String namespaceURI,
	String localName,
	double value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(Double.toString(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByDouble(
	Element element,
	String namespaceURI,
	String localName,
	Double value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByDoubleList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByDouble(
	Element element,
	double value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(Double.toString(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByDouble(
	Element element,
	String namespaceURI,
	String localName,
	double value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, Double.toString(value));
    }

    public static void setAttributePropertyByDouble(
	Element element,
	String namespaceURI,
	String localName,
	Double value,
	RNSContext nsContext
    ) {
	element.setAttributeNS(namespaceURI, localName, value.toString());
    }

    // BigDecimal type
    public static BigDecimal getElementPropertyAsBigDecimal(
	Element element
    ) {
	String text = element2Data(element);
	return (new BigDecimal(text));
    }

    public static BigDecimal getElementPropertyAsBigDecimal(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (new BigDecimal(text));
    }

    public static List getElementPropertyAsBigDecimalList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new BigDecimal(element2Data(nodes[i])));
	}
	return (list);
    }

    public static BigDecimal getElementPropertyAsBigDecimalByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsBigDecimal(property));
    }

    public static List getElementPropertyAsBigDecimalListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new BigDecimal(element2Text(property)));
	}
	return (list);
    }

    public static BigDecimal getAttributePropertyAsBigDecimal(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new BigDecimal(value));
	}
    }

    public static void setElementPropertyByBigDecimal(
	Element element,
	String namespaceURI,
	String localName,
	BigDecimal value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByBigDecimalList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByBigDecimal(
	Element element,
	BigDecimal value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(value.toString());
	element.appendChild(text);
    }

    public static void setAttributePropertyByBigDecimal(
	Element element,
	String namespaceURI,
	String localName,
	BigDecimal value,
	RNSContext nsContext
    ) {
	if (value != null) {
	    element.setAttributeNS(namespaceURI, localName, value.toString());
	}
    }

    // BigInteger type
    public static BigInteger getElementPropertyAsBigInteger(
	Element element
    ) {
	String text = element2Data(element);
	return (new BigInteger(text));
    }

    public static BigInteger getElementPropertyAsBigInteger(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (new BigInteger(text));
    }

    public static List getElementPropertyAsBigIntegerList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(new BigInteger(element2Data(nodes[i])));
	}
	return (list);
    }

    public static BigInteger getElementPropertyAsBigIntegerByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsBigInteger(property));
    }

    public static List getElementPropertyAsBigIntegerListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(new BigInteger(element2Text(property)));
	}
	return (list);
    }

    public static BigInteger getAttributePropertyAsBigInteger(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (new BigInteger(value));
	}
    }

    public static void setElementPropertyByBigInteger(
	Element element,
	String namespaceURI,
	String localName,
	BigInteger value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByBigIntegerList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByBigInteger(
	Element element,
	BigInteger value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(value.toString());
	element.appendChild(text);
    }

    public static void setAttributePropertyByBigInteger(
	Element element,
	String namespaceURI,
	String localName,
	BigInteger value,
	RNSContext nsContext
    ) {
	if (value != null) {
	    element.setAttributeNS(namespaceURI, localName, value.toString());
	}
    }

    // Date type
    public static Date getElementPropertyAsDate(
	Element element
    ) {
	try {
	    String text = element2Data(element);
	    DateFormat df = DateFormat.getDateInstance();
	    return (df.parse(text));
	} catch (ParseException e) {
	    throw (new IllegalArgumentException(e.getMessage()));
	}
    }

    public static Date getElementPropertyAsDate(
	Element element,
	String namespaceURI,
	String localName
    ) {
	try {
	    Element property = getOnlyElement(element, namespaceURI, localName);
	    String text = element2Data(property);
	    DateFormat df = DateFormat.getDateInstance();
	    return (df.parse(text));
	} catch (ParseException e) {
	    throw (new IllegalArgumentException(e.getMessage()));
	}
    }

    public static List getElementPropertyAsDateList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	try {
	    Element[] nodes = getElements(element, namespaceURI, localName);
	    DateFormat df = DateFormat.getDateInstance();
	    List list = new ArrayList();
	    for (int i = 0;i < nodes.length;i++) {
		list.add(df.parse(element2Data(nodes[i])));
	    }
	    return (list);
	} catch (ParseException e) {
	    throw (new IllegalArgumentException(e.getMessage()));
	}
    }

    public static Date getElementPropertyAsDateByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsDate(property));
    }

    public static List getElementPropertyAsDateListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    String value = element2Text(property);
	    try {
		DateFormat df = DateFormat.getDateInstance();
		list.add(df.parse(value));
	    } catch (ParseException e) {
		throw (new IllegalArgumentException(e.getMessage()));
	    }
	}
	return (list);
    }

    public static Date getAttributePropertyAsDate(
	Element element,
	String namespaceURI,
	String localName
    ) {
	try {
	    String value = getAttribute(element, namespaceURI, localName);
	    if (value == null) {
		return (null);
	    } else {
		DateFormat df = DateFormat.getDateInstance();
		return (df.parse(value));
	    }
	} catch (ParseException e) {
	    throw (new IllegalArgumentException(e.getMessage()));
	}
    }

    public static void setElementPropertyByDate(
	Element element,
	String namespaceURI,
	String localName,
	Date value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	DateFormat df = DateFormat.getDateInstance();
	Text text = doc.createTextNode(df.format(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByDateList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByDate(
	Element element,
	Date value
    ) {
	Document doc = element.getOwnerDocument();
	DateFormat df = DateFormat.getDateInstance();
	Text text = doc.createTextNode(df.format(value));
	element.appendChild(text);
    }

    public static void setAttributePropertyByDate(
	Element element,
	String namespaceURI,
	String localName,
	Date value,
	RNSContext nsContext
    ) {
	if (value != null) {
	    DateFormat df = DateFormat.getDateInstance();
	    element.setAttributeNS(namespaceURI, localName, df.format(value));
	}
    }

    // Locale type
    public static Locale getElementPropertyAsLocale(
	Element element
    ) {
	String text = element2Data(element);
	return (makeLocale(text));
    }

    public static Locale getElementPropertyAsLocale(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (makeLocale(text));
    }

    public static List getElementPropertyAsLocaleList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(makeLocale(element2Data(nodes[i])));
	}
	return (list);
    }

    public static Locale getElementPropertyAsLocaleByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsLocale(property));
    }

    public static List getElementPropertyAsLocaleListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(makeLocale(element2Text(property)));
	}
	return (list);
    }

    public static Locale getAttributePropertyAsLocale(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (makeLocale(value));
	}
    }

    public static void setElementPropertyByLocale(
	Element element,
	String namespaceURI,
	String localName,
	Locale value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByLocaleList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByLocale(
	Element element,
	Locale value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(value.toString());
	element.appendChild(text);
    }

    public static void setAttributePropertyByLocale(
	Element element,
	String namespaceURI,
	String localName,
	Locale value,
	RNSContext nsContext
    ) {
	if (value != null) {
	    element.setAttributeNS(namespaceURI, localName, value.toString());
	}
    }

    // URL type
    public static URL getElementPropertyAsURL(
	Element element
    ) {
	String text = element2Data(element);
	return (makeURL(text));
    }

    public static URL getElementPropertyAsURL(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (makeURL(text));
    }

    public static List getElementPropertyAsURLList(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(makeURL(element2Data(nodes[i])));
	}
	return (list);
    }

    public static URL getElementPropertyAsURLByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsURL(property));
    }

    public static List getElementPropertyAsURLListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(makeURL(element2Text(property)));
	}
	return (list);
    }

    public static URL getAttributePropertyAsURL(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String value = getAttribute(element, namespaceURI, localName);
	if (value == null) {
	    return (null);
	} else {
	    return (makeURL(value));
	}
    }

    public static void setElementPropertyByURL(
	Element element,
	String namespaceURI,
	String localName,
	URL value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(value.toString());
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByURLList(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	String prefix = nsContext.getPrefixByUri(namespaceURI);
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	    property.setPrefix(prefix);
	    Text text = doc.createTextNode(values.get(i).toString());
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByURL(
	Element element,
	URL value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(value.toString());
	element.appendChild(text);
    }

    public static void setAttributePropertyByURL(
	Element element,
	String namespaceURI,
	String localName,
	URL value,
	RNSContext nsContext
    ) {
	if (value != null) {
	    element.setAttributeNS(namespaceURI, localName, value.toString());
	}
    }

    // binary type
    public static byte[] getElementPropertyAsBinaryBASE64(
	Element element
    ) {
	String text = element2Data(element);
	return (makeBytesByBASE64(text));
    }

    public static byte[] getElementPropertyAsBinaryBASE64(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element property = getOnlyElement(element, namespaceURI, localName);
	String text = element2Data(property);
	return (makeBytesByBASE64(text));
    }

    public static List getElementPropertyAsBinaryListBASE64(
	Element element,
	String namespaceURI,
	String localName
    ) {
	Element[] nodes = getElements(element, namespaceURI, localName);
	List list = new ArrayList();
	for (int i = 0;i < nodes.length;i++) {
	    list.add(makeBytesByBASE64(element2Data(nodes[i])));
	}
	return (list);
    }

    public static byte[] getElementPropertyAsBinaryBASE64ByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	if (stack.isEmptyElement()) {
	    return (null);
	}
	Element property = stack.peekElement();
	if (!isTargetElement(property, namespaceURI, localName)) {
	    return (null);
	}
	stack.popElement();
	return (getElementPropertyAsBinaryBASE64(property));
    }

    public static List getElementPropertyAsBinaryBASE64ListByStack(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	List list = new ArrayList();
	for (;;) {
	    if (stack.isEmptyElement()) {
		break;
	    }
	    Element property = stack.peekElement();
	    if (!isTargetElement(property, namespaceURI, localName)) {
		break;
	    }
	    stack.popElement();
	    list.add(getElementPropertyAsBinaryBASE64(property));
	}
	return (list);
    }

    public static void setElementPropertyByBinaryBASE64(
	Element element,
	String namespaceURI,
	String localName,
	byte[] value,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	Text text = doc.createTextNode(makeStringAsBASE64(value));
	property.appendChild(text);
	element.appendChild(property);
    }

    public static void setElementPropertyByBinaryListBASE64(
	Element element,
	String namespaceURI,
	String localName,
	List values,
	RNSContext nsContext
    ) {
	Document doc = element.getOwnerDocument();
	int size = values.size();
	for (int i = 0;i < size;i++) {
	    Element property = doc.createElementNS(namespaceURI, localName);
	property.setPrefix(nsContext.getPrefixByUri(namespaceURI));
	    Text text = doc.createTextNode(
		makeStringAsBASE64((byte[])values.get(i))
	    );
	    property.appendChild(text);
	    element.appendChild(property);
	}
    }

    public static void setElementPropertyByBinaryBASE64(
	Element element,
	byte[] value
    ) {
	Document doc = element.getOwnerDocument();
	Text text = doc.createTextNode(makeStringAsBASE64(value));
	element.appendChild(text);
    }

    //
    // matchers
    //

    public static boolean isTargetElement(
	Element element,
	String namespaceURI,
	String localName
    ) {
	String elementURI = element.getNamespaceURI();
	if (elementURI != null) {
	    return (
		namespaceURI.equals(elementURI) &&
		localName.equals(element.getLocalName())
	    );
	} else {
	    return (localName.equals(element.getTagName()));
	}
    }

    public static boolean hasAttribute(
	Element element,
	String namespaceURI,
	String attrName
    ) {
	return (getAttribute(element, namespaceURI, attrName) != null);
    }

    public static String getAttribute(
	Element element,
	String namespaceURI,
	String attrName
    ) {
	Attr attr = element.getAttributeNodeNS(namespaceURI, attrName);
	if (attr == null) {
	    return (null);
	}
	return (attr.getValue());
    }

    public static boolean isSequence(
	RStack stack,
	String namespaceURI,
	String localName
    ) {
	Element[] elements = stack.peekElements();
	if (elements == null) {
	    return (false);
	}
	if (elements.length != 1) {
	    return (false);
	}
	return (isTargetElement(elements[0], namespaceURI, localName));
    }

    public static boolean isSequence(
	RStack stack,
	String namespaceURI,
	String[] names
    ) {
	Element[] elements = stack.peekElements();
	if (elements == null) {
	    return (false);
	}
	if (elements.length != names.length) {
	    return (false);
	}
	for (int i = 0;i < names.length;i++) {
	    if (!isTargetElement(elements[i], namespaceURI, names[i])) {
		return (false);
	    }
	}
	return (true);
    }

    public static Element getOnlyElement(
	Element element,
	String namespaceURI,
	String localName
    ) throws IllegalArgumentException {
	Element[] nodes = getElements(element, namespaceURI, localName);
	switch (nodes.length) {

	case 0:
	    return (null);
	case 1:
	    break;
	default:
	    throw (new IllegalArgumentException());
	}
	return (nodes[0]);
    }

    public static Element[] getElements(
	Element element,
	String namespaceURI,
	String localName
    ) {
	NodeList children = element.getChildNodes();
	List list = new ArrayList();
	int size = children.getLength();
	for (int i = 0;i < size;i++) {
	    Node child = children.item(i);
	    if (child.getNodeType() == Node.ELEMENT_NODE) {
		Element childElement = (Element)child;
		if (isTargetElement(childElement, namespaceURI, localName)) {
		    list.add(childElement);
		}
	    }
	}
	Element[] array = new Element[list.size()];
	return ((Element[])list.toArray(array));
    }

    public static String element2Data(Element element) {
	return (URelaxer.element2Data(element));
    }

    public static String element2Text(Element element) {
	return (URelaxer.element2Text(element));
    }

    public static Locale makeLocale(String name) {
	return (URelaxer.makeLocale(name));
    }

    public static URL makeURL(String name) {
	return (URelaxer.makeURL(name));
    }

    public static byte[] makeBytesByBASE64(String data) {
	return (URelaxer.makeBytesByBASE64(data));
    }

    public static String makeStringAsBASE64(byte[] data) {
	return (URelaxer.makeStringAsBASE64(data));
    }
}
