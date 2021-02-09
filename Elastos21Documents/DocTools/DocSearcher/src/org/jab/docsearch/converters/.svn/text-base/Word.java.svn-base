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

import org.apache.poi.hwpf.extractor.WordExtractor;
import org.apache.poi.poifs.eventfilesystem.POIFSReader;

/**
 * Class for handling MS Word files
 * 
 * @version $Id: Word.java,v 1.1 2006/06/15 16:08:00 henschel Exp $
 */
public class Word extends AbstractConverter {
    private String fileName;


    /**
     * Constructor
     */
    private Word() {
        // protect this constructor
    }


    /**
     * Constructor
     *
     * @param fileName
     */
    public Word(String fileName) {
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
        catch (IOException ioe) {
            logger.error("parse() failed with IEException", ioe);
        }
        catch (Exception e) {
            logger.error("parse() failed", e);
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
            logger.debug("parse() Word file='" + fileName + "' \ntitle='" + documentTitle + "' \nauthor='" + documentAuthor + "' \nkeywords='" + documentKeywords + "'");
        }

        // get text
        try {
            fin = new FileInputStream(fileName);

            WordExtractor we = new WordExtractor(fin);

            // get text
            documentText = we.getText();

            fin.close();
        }
        catch (IOException ioe) {
            logger.error("parse() failed with IOException", ioe);
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
            logger.debug("parse() text='" + documentText + "'");
        }
    }
}
