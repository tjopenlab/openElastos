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

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;
import org.pdfbox.encryption.DocumentEncryption;
import org.pdfbox.pdfparser.PDFParser;
import org.pdfbox.pdmodel.PDDocument;
import org.pdfbox.pdmodel.PDDocumentInformation;
import org.pdfbox.util.PDFTextStripper;

import org.jab.docsearch.utils.FileUtils;
import org.jab.docsearch.utils.Utils;

/**
 * This class extra text of PDF document
 * 
 * @version $Id: PdfToText.java,v 1.9 2005/10/09 20:13:15 henschel Exp $
 */
public class PdfToText {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    private static final String DEFAULT_ENCODING = "ISO-8859-1";
    // "US-ASCII";
    // "UTF-8";
    // private static final String PASSWORD = "-password";
    private String fileName;
    private String tempFile = "";
    private StringBuffer errMsgBuf = new StringBuffer();
    private String author = "";
    private String title = "";
    private String keywords = "";
    private String summary = "";
    private boolean foundText = false;


    /**
     * Main method
     *
     * @param args
     */
    public static void main(String[] args) {
        BasicConfigurator.configure();
        Logger mainLogger = Logger.getLogger(PdfToText.class);
        
        int numArgs = args.length;
        if (numArgs < 2) {
            mainLogger.debug("USAGE:\n\tjava PdfToText pdf_file.pdf tempTextFile.txt");
        }
        else {
            PdfToText ptt = new PdfToText(args[0], args[1]);
            try {
                // parse
                boolean foundText = ptt.doMultiValent();
                // boolean foundText = ptt.parse();

                // found meta data
                boolean foundMetaData = false;
                if (ptt.getAuthor() != null ||
                        ptt.getTitle() != null ||
                        ptt.getKeywords() != null ||
                        ptt.getSummary() != null) {
                    foundMetaData = true;
                }
                    
                if (foundMetaData && foundText) {
                    mainLogger.info("SUCCESS: \n\tTitle:" + ptt.getTitle() + "\n\tAuthor:" + ptt.getAuthor() + "\n\tSum:" + ptt.getSummary());
                }
                else if (foundText) {
                    mainLogger.info("UNSUCCESSFUL FOR META DATA ONLY");
                }
                else {
                    mainLogger.info("COMPLETELY UNSUCCESSFUL!");
                }
            }
            catch (Exception e) {
                mainLogger.error("main()", e);
            }
        }
    }


    /**
     * Cronstructor
     *
     * @param fileName  PDF file
     * @param tempFile  tmp file
     */
    public PdfToText(String fileName, String tempFile) {
        this.fileName = fileName;
        this.tempFile = tempFile;
    }


    /**
     * Add error text to buffer
     *
     * @param toAdd
     */
    private void addErrText(String toAdd) {
        errMsgBuf.append(toAdd);
        errMsgBuf.append('\n');
    }


    /**
     * Return error mtest
     *
     * @return  error text
     */
    public String getErrText() {
        return errMsgBuf.toString();
    }


    /**
     * Method disParse
     *
     * @return
     */
    public boolean didParse() {
        try {
            parse();
        } catch (Exception e) {
            logger.error("didParse() failed", e);
            addErrText("PDFBOX error: " + e.toString());
        }

        return foundText;
    }


    /**
     * Parse PDF with PDF Box
     *
     * @throws Exception
     */
    private void parse() throws Exception {
        foundText = false;

        if (logger.isDebugEnabled()) {
            logger.debug("parse() PDFBox Extraction Stripper instantiated for (" + fileName + " with output to: (" + tempFile + ")");
        }
        
        String password = "";
        String encoding = DEFAULT_ENCODING;
        PDFTextStripper stripper = new PDFTextStripper();
        InputStream input = new FileInputStream(fileName);
        PDDocument document = parseDocument(input);

        // encryption
        if (document.isEncrypted()) {
            DocumentEncryption decryptor = new DocumentEncryption(document);
            if (logger.isDebugEnabled()) {
                logger.debug("parse() Document (" + fileName + ") appears to be encrypted.");
            }
            decryptor.decryptDocument(password);
        }

        // write the text to the file
        Writer output = null;
        try {
            if (logger.isDebugEnabled()) {
                logger.debug("parse() Attempting to extract text from (" + fileName + ") \n\tto: (" + tempFile + ")");
            }

            output = new OutputStreamWriter(new FileOutputStream(tempFile), encoding);
            stripper.writeText(document, output);

            foundText = true;

            if (logger.isDebugEnabled()) {
                logger.debug("parse() Successfully stripped out text from (" + fileName + ") \n\tto: (" + tempFile + ")");
            }
        }
        catch (IOException ioe) {
            logger.error("parse() failed", ioe);
            addErrText("PDF Box PARSE Error: " + ioe.toString());
        }
        finally {
            if (output != null) {
                try {
                    output.close();
                }
                catch (IOException ioe) {
                    logger.fatal("parse() can't close OutputStream", ioe);
                }
            }
        }

        // get the meta data
        PDDocumentInformation info = document.getDocumentInformation();
        author = info.getAuthor();
        title = info.getTitle();
        keywords = info.getKeywords();
        summary = info.getSubject();

        document.close();
    }


    /**
     * Method return title of document
     *
     * @return  title of document
     */
    public String getTitle() {
        return title;
    }


    /**
     * Method return author of document
     *
     * @return  author of document
     */

    public String getAuthor() {
        return author;
    }


    /**
     * Method return summary of document
     *
     * @return  summary of document
     */

    public String getSummary() {
        return summary;
    }


    /**
     * Method return keywords of document
     *
     * @return  keywords of document
     */
    public String getKeywords() {
        return keywords;
    }


    /**
     * Method doMultiValent
     *
     * @return
     */
    public boolean doMultiValent() {
        boolean retB = false;

        File filein = new File(fileName);

        try {
            tool.doc.ExtractText tpe = new tool.doc.ExtractText();
            // tpe.setCache(new File(System.getProperty("java.io.tmpdir")));
            tpe.setVerbose(false);

            StringBuffer sb = new StringBuffer();
            sb.append(tpe.extract(filein.toURI(), "text/pdf"));

            String testBreaks = sb.toString();
            testBreaks = Utils.replaceAll("==============================================", testBreaks, "\n");

            StringBuffer saveB = new StringBuffer();
            saveB.append(testBreaks);

            FileUtils.saveFile(tempFile, saveB);

            foundText = true;
            retB = true;
        }
        catch (Exception e) {
            logger.error("diMultiValent() failed", e);
            addErrText("Multivalent text extraction failed:" + e.toString());
            retB = false;
        }

        return retB;
    }


    /**
     * Method parseDocument
     *
     * @param input
     * @return
     * @throws IOException
     */
    private PDDocument parseDocument(InputStream input) throws IOException {
        PDFParser parser = new PDFParser(input);
        
        parser.parse();
        
        return parser.getPDDocument();
    }
}
