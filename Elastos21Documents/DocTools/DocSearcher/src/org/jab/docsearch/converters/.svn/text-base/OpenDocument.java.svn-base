/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package org.jab.docsearch.converters;

import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Class for handling OpenDocument files
 *
 * OpenDocument Text    .odt
 * 
 * @version $Id: OpenDocument.java,v 1.5 2006/06/15 16:08:00 henschel Exp $
 */
public class OpenDocument extends AbstractConverter {
    private final static String CONTENT_FILE = "content.xml";
    private final static String META_FILE = "meta.xml";
    private final static String DC_CREATOR_TAG = "dc:creator";
    private final static String DC_TITLE_TAG = "dc:title";
    private final static String OFFICE_BODY_TAG = "office:body";
    private final static String OFFICE_META_TAG = "office:meta";
    private String fileName;

    /**
     * Constructor
     */
    private OpenDocument() {
        // protect this constructor
    }


    /**
     * Constructor
     *
     * @param fileName
     */
    public OpenDocument(String fileName) {
        this.fileName = fileName;
    }


    /**
     * Parse OpenDocument file
     *
     * @throws IOException
     */
    public void parse() throws IOException {

        // zip
        ZipFile zip = null;
        try {
            zip = new ZipFile(fileName);

            // meta file
            {
                ZipEntry metaZipEntry = zip.getEntry(META_FILE);
                if (metaZipEntry != null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("parse() found meta file (" + metaZipEntry.getName() + ")");
                    }
    
                    // read xml with SAX2
                    try {
                        // configure the sax parser factory
                        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
                        saxParserFactory.setValidating(false);
                        saxParserFactory.setNamespaceAware(false);
        
                        // create sax parser
                        SAXParser saxParser = saxParserFactory.newSAXParser();
                        MetaSAXDefaultHandler saxHandler = new MetaSAXDefaultHandler();
    
                        // create xml reader
                        XMLReader xmlReader = saxParser.getXMLReader();
                        xmlReader.setContentHandler(saxHandler);
                        xmlReader.setErrorHandler(saxHandler);
                        xmlReader.setEntityResolver(saxHandler);
    
                        // set source
                        InputSource is = new InputSource(zip.getInputStream(metaZipEntry));
    
                        // action!
                        xmlReader.parse(is);
    
                        // get title
                        if (saxHandler.titleText.length() != 0) {
                            documentTitle = saxHandler.titleText.toString();
                        }
                        if (logger.isDebugEnabled()) {
                            logger.debug("parse() title='" + documentTitle + "'");
                        }
    
                        // get author
                        if (saxHandler.creatorText.length() != 0) {
                            documentAuthor = saxHandler.creatorText.toString();
                        }
                        if (logger.isDebugEnabled()) {
                            logger.debug("parse() author='" + documentAuthor + "'");
                        }
                    }
                    catch (ParserConfigurationException pce) {
                        logger.error("parse() failed", pce);
                    }
                    catch (SAXException se) {
                        logger.error("parse() failed", se);
                    }
                }
            }

            // content file
            {
                ZipEntry contentZipEntry = zip.getEntry(CONTENT_FILE);
                if (contentZipEntry != null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("parse() found content file (" + contentZipEntry.getName() + ")");
                    }
    
                    // read xml with SAX2
                    try {
                        // configure the sax parser factory
                        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
                        saxParserFactory.setValidating(false);
                        saxParserFactory.setNamespaceAware(false);
        
                        // create sax parser
                        SAXParser saxParser = saxParserFactory.newSAXParser();
                        ContentSAXDefaultHandler saxHandler = new ContentSAXDefaultHandler();
    
                        // create xml reader
                        XMLReader xmlReader = saxParser.getXMLReader();
                        xmlReader.setContentHandler(saxHandler);
                        xmlReader.setErrorHandler(saxHandler);
                        xmlReader.setEntityResolver(saxHandler);
    
                        // set source
                        InputSource is = new InputSource(zip.getInputStream(contentZipEntry));
    
                        // action!
                        xmlReader.parse(is);
    
                        // get text
                        if (saxHandler.text.length() != 0) {
                            documentText = saxHandler.text.toString();
                        }
                        if (logger.isDebugEnabled()) {
                            logger.debug("parse() text='" + documentText + "'");
                        }
                    }
                    catch (ParserConfigurationException pce) {
                        logger.error("parse() failed", pce);
                    }
                    catch (SAXException se) {
                        logger.error("parse() failed", se);
                    }
                }
            }
        }
        catch (IOException ioe) {
            logger.fatal("parse() failed with IOException", ioe);
            throw ioe;
        }
        finally {
            try {
                if (zip != null) {
                    zip.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("parse() can't close ZipFile", ioe);
            }
        }
    }


    /**
     * SAXDefaultHandler for meta.xml
     */
    private class MetaSAXDefaultHandler extends DefaultHandler {
        private boolean metaTag = false;
        private boolean titleTag = false;
        private boolean creatorTag = false;
        private StringBuffer titleText = new StringBuffer();
        private StringBuffer creatorText = new StringBuffer();

        /**
         * overwrite startElement method of ContentHandler
         *
         * @param uri            Description of the Parameter
         * @param localName      Description of the Parameter
         * @param qName          Description of the Parameter
         * @param attributes     Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void startElement(String uri, String localName, String qName, Attributes attributes)
                 throws SAXException {

            // check for office:meta
            if (! metaTag) {
                if (OFFICE_META_TAG.equals(qName)) {
                    metaTag = true;
                    return;
                }
            }
            else {
                // check for dc:title
                if (! titleTag) {
                    if (DC_TITLE_TAG.equals(qName)) {
                        titleTag = true;
                        return;
                    }
                }
    
                // check for dc:creator
                if (! creatorTag) {
                    if (DC_CREATOR_TAG.equals(qName)) {
                        creatorTag = true;
                        return;
                    }
                }
            }
        }


        /**
         * overwrite endElement method of ContentHandler
         *
         * @param uri            Description of the Parameter
         * @param localName      Description of the Parameter
         * @param qName          Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void endElement(String uri, String localName, String qName)
                 throws SAXException {

            if (metaTag) {
                // check for dc:title
                if (titleTag) {
                    if (DC_TITLE_TAG.equals(qName)) {
                        titleTag = false;
                        return;
                    }
                }

                // check for dc:creator
                if (creatorTag) {
                    if (DC_CREATOR_TAG.equals(qName)) {
                        creatorTag = false;
                    }
                }

                // check for office:meta
                if (metaTag) {
                    if (OFFICE_META_TAG.equals(qName)) {
                        metaTag = false;
                    }
                }
            }
        }


        /**
         * overwrite characters method of ContentHandler
         *
         * @param ch             Description of the Parameter
         * @param start          Description of the Parameter
         * @param length         Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void characters(char[] ch, int start, int length)
                 throws SAXException {

            // title
            if (titleTag) {
                titleText.append(ch, start, length);
            }
            // creator
            else if (creatorTag) {
                creatorText.append(ch, start, length);
            }
        }


        /**
         * overwrite warning method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void warning(SAXParseException spe)
                 throws SAXException {
            logger.warn("warning()", spe);
        }



        /**
         * overwrite error method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void error(SAXParseException spe)
                 throws SAXException {
            throw spe;
        }



        /**
         * overwrite fatalError method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void fatalError(SAXParseException spe)
                 throws SAXException {
            throw spe;
        }
    }


    /**
     * SAXDefaultHandler for content.xml
     */
    private class ContentSAXDefaultHandler extends DefaultHandler {
        private boolean bodyTag = false;
        private StringBuffer text = new StringBuffer();

        /**
         * overwrite startElement method of ContentHandler
         *
         * @param uri            Description of the Parameter
         * @param localName      Description of the Parameter
         * @param qName          Description of the Parameter
         * @param attributes     Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void startElement(String uri, String localName, String qName, Attributes attributes)
                 throws SAXException {
            // check for office:body
            if (! bodyTag) {
                if (OFFICE_BODY_TAG.equals(qName)) {
                    bodyTag = true;
                    return;
                }
            }
        }


        /**
         * overwrite endElement method of ContentHandler
         *
         * @param uri            Description of the Parameter
         * @param localName      Description of the Parameter
         * @param qName          Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void endElement(String uri, String localName, String qName)
                 throws SAXException {

            // check for office:body
            if (bodyTag) {
                if (OFFICE_BODY_TAG.equals(qName)) {
                    bodyTag = false;
                }
            }
        }


        /**
         * overwrite characters method of ContentHandler
         *
         * @param ch             Description of the Parameter
         * @param start          Description of the Parameter
         * @param length         Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void characters(char[] ch, int start, int length)
                 throws SAXException {
            if (bodyTag) {
                text.append(ch, start, length);
            }
        }


        /**
         * overwrite warning method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void warning(SAXParseException spe)
                 throws SAXException {
            logger.warn("warning()", spe);
        }



        /**
         * overwrite error method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void error(SAXParseException spe)
                 throws SAXException {
            throw spe;
        }



        /**
         * overwrite fatalError method of ErrorHandler
         *
         * @param spe            Description of the Parameter
         * @throws SAXException  Description of the Exception
         */
        public void fatalError(SAXParseException spe)
                 throws SAXException {
            throw spe;
        }
    }
}
