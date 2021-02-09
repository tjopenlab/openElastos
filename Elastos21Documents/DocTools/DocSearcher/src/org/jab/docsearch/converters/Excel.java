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

import java.io.FileInputStream;
import java.io.IOException;

import org.apache.poi.hssf.eventusermodel.HSSFEventFactory;
import org.apache.poi.hssf.eventusermodel.HSSFRequest;
import org.apache.poi.poifs.eventfilesystem.POIFSReader;
import org.apache.poi.poifs.filesystem.DocumentInputStream;
import org.apache.poi.poifs.filesystem.POIFSFileSystem;

/**
 * Class for handling MS Excel files
 * 
 * @version $Id: Excel.java,v 1.1 2006/06/15 16:08:00 henschel Exp $
 */
public class Excel extends AbstractConverter {
    private String fileName;

    /**
     * Contructor
     */
    private Excel() {
        // protect this constructor
    }


    /**
     * Contructor
     *
     * @param fileName
     * @param tempFile
     */
    public Excel(String fileName) {
        this.fileName = fileName;
    }


    /**
     * Parse Word file
     *
     * @throws IOException
     */
    public void parse() throws IOException {

        // get meta data
        FileInputStream fin = null;
        try {
            fin = new FileInputStream(fileName);
            
            POIFSReader r = new POIFSReader();
            MyPOIFSReaderListener mpfsrl = new MyPOIFSReaderListener();
            r.registerListener(mpfsrl, "\005SummaryInformation");
            r.read(fin);

            fin.close();

            // get meta data
            documentTitle = mpfsrl.getTitle();
            documentAuthor = mpfsrl.getAuthor();
            documentKeywords = mpfsrl.getKeywords();
        }
        catch (Exception e) {
            logger.error("parse() failed for Excel file=" + fileName, e);
        }
        finally {
            try {
                if (fin != null) {
                    fin.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("parse() can't close FileInputStream", ioe);
            }
        }
        
        if (logger.isDebugEnabled()) {
            logger.debug("parse() Excel file='" + fileName + "' \ntitle='" + documentTitle + "' \nauthor='" + documentAuthor + "' \nkeywords='" + documentKeywords + "'");
        }
        
        // get text
        DocumentInputStream din = null;
        ExcelListener el = new ExcelListener();
        try {
            // proceed to write to file
            // create a new file input stream with the input file specified
            // at the command line
            fin = new FileInputStream(fileName);

            POIFSFileSystem poifs = new POIFSFileSystem(fin);
            din = poifs.createDocumentInputStream("Workbook");
            HSSFRequest req = new HSSFRequest();
            req.addListenerForAllRecords(el);
            HSSFEventFactory factory = new HSSFEventFactory();
            factory.processEvents(req, din);

            fin.close();
            
            // get text
            documentText = el.getText().toString();
        }
        catch (IOException ioe) {
            logger.error("parse() failed with IOException", ioe);
        }
        catch (Exception e) {
            logger.error("parse() failed for Excel file=" + fileName, e);
        }
        finally {
            try {
                if (din != null) {
                    din.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("parse() can't close DocumentInputStream", ioe);
            }

            try {
                if (fin != null) {
                    fin.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("parse() can't close FileInputStream", ioe);
            }
        }

        if (logger.isDebugEnabled()) {
            logger.debug("parse() text='" + documentText + "'");
        }
    }
}
