package jp.gr.java_conf.abagames.bulletml;

import java.lang.reflect.*;
import java.io.*;
import java.net.URL;
import java.net.MalformedURLException;
import javax.xml.parsers.*;
import org.xml.sax.*;
import org.w3c.dom.*;

/**
 * UJAXP
 *
 * @since   Feb. 20, 2000
 * @version Jan. 13, 2001
 * @author  ASAMI, Tomoharu (asami@zeomtech.com)
 */
public final class UJAXP {
    private static ErrorHandler errorHandler;

    public static Document getDocument(File file)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(file.toURL()));
    }

    public static Document getDocument(String uri)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(uri, getErrorHandler()));
    }

    public static Document getDocument(URL url)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(url, getErrorHandler()));
    }

    public static Document getDocument(InputStream in)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(in, getErrorHandler()));
    }

    public static Document getDocument(InputSource is)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(is, getErrorHandler()));
    }

    public static Document getDocument(Reader reader)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(reader, getErrorHandler()));
    }

    public static Document getDocument(File file, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	return (getDocument(file.toURL(), handler));
    }

    public static Document getDocument(String uri, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(uri);
        return (doc);
    }

    public static Document getDocument(URL url, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(url.toString());
        return (doc);
    }

    public static Document getDocument(InputStream in, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(in);
        return (doc);
    }

    public static Document getDocument(InputSource is, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(is);
        return (doc);
    }

    public static Document getDocument(Reader reader, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(new InputSource(reader));
        return (doc);
    }

    public static Document getValidDocument(File file)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(file.toURL()));
    }

    public static Document getValidDocument(String uri)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(uri, getErrorHandler()));
    }

    public static Document getValidDocument(URL url)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(url, getErrorHandler()));
    }

    public static Document getValidDocument(InputStream in)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(in, getErrorHandler()));
    }

    public static Document getValidDocument(InputSource is)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(is, getErrorHandler()));
    }

    public static Document getValidDocument(Reader reader)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(reader, getErrorHandler()));
    }

    public static Document getValidDocument(File file, ErrorHandler handler)
	throws IOException, SAXException, ParserConfigurationException {

	return (getValidDocument(file.toURL(), handler));
    }

    public static Document getValidDocument(
	String uri,
	ErrorHandler handler
    ) throws IOException, SAXException, ParserConfigurationException {
	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(uri);
        return (doc);
    }

    public static Document getValidDocument(
	URL url,
	ErrorHandler handler
    ) throws IOException, SAXException, ParserConfigurationException {
	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(url.toString());
        return (doc);
    }

    public static Document getValidDocument(
	InputStream in,
	ErrorHandler handler
    ) throws IOException, SAXException, ParserConfigurationException {
	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(in);
        return (doc);
    }

    public static Document getValidDocument(
	InputSource is,
	ErrorHandler handler
    ) throws IOException, SAXException, ParserConfigurationException {
	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(is);
        return (doc);
    }

    public static Document getValidDocument(
	Reader reader,
	ErrorHandler handler
    ) throws IOException, SAXException, ParserConfigurationException {
	if (handler == null) {
	    handler = getErrorHandler();
	}
        DocumentBuilderFactory factory
            = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
        Document doc = builder.parse(new InputSource(reader));
        return (doc);
    }

    public static Document makeDocument()
	throws ParserConfigurationException {

	return (makeDocument(getErrorHandler()));
    }

    public static Document makeDocument(ErrorHandler handler)
	throws ParserConfigurationException {

	DocumentBuilderFactory factory
	    = DocumentBuilderFactory.newInstance();
	factory.setValidating(true);
	DocumentBuilder builder = factory.newDocumentBuilder();
	builder.setErrorHandler(handler);
	Document doc = builder.newDocument();
	return (doc);
    }

    public static ErrorHandler getErrorHandler() {
	if (errorHandler == null) {
	    errorHandler = new ErrorHandler() {
		public void error(SAXParseException e) {
		    System.out.print("error : ");
		    System.out.println(e.getMessage());
		}

		public void fatalError(SAXParseException e) {
		    System.out.print("fatal error : ");
		    System.out.println(e.getMessage());
		}

		public void warning(SAXParseException e) {
		    System.out.print("warning : ");
		    System.out.println(e.getMessage());
		}
	    };
	}
	return (errorHandler);
    }

    public static void setErrorHandler(ErrorHandler handler) {
	errorHandler = handler;
    }

    // test driver
    public static void main(String[] args) throws Exception {
	String className = args[0];
	File file = new File(args[1]);
	Class clazz = Class.forName(className);
	Method setupMethod = clazz.getMethod(
	    "setup",
	    new Class[] { File.class }
	);
	Method makeMethod = clazz.getMethod(
	    "makeDocument",
	    new Class[0]
	);
	Object object = clazz.newInstance();
	setupMethod.invoke(object, new Object[] { file });
	Document doc = (Document)makeMethod.invoke(object, new Object[0]);
	System.out.println(URelaxer.doc2String4Data(doc));
    }
}
