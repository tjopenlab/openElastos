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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import org.apache.log4j.Logger;

/**
 * Class OoToTest
 * 
 * @version $Id: OoToText.java,v 1.3 2005/10/08 15:52:08 henschel Exp $
 */
public class OoToText {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    private final int BUFFER = 2048;
    private final static String CONTENT_FILE = "content.xml";
    private final static String META_FILE = "meta.xml";
    private String fileName;
    private String tempFile;
    private String metaFile;


    /**
     * Constructor
     *
     * @param fileName
     * @param tempFile
     * @param metaFile
     */
    public OoToText(String fileName, String tempFile, String metaFile) {
        this.fileName = fileName;
        this.tempFile = tempFile;
        this.metaFile = metaFile;
    }


    /**
     * Parse Oo document
     *
     * @throws IOException
     */
    public void parse() throws IOException {
        // 1st convert the file to uncompressed xml

        ZipInputStream zis = null;

        int count;
        byte[] data = new byte[BUFFER];
        try {
            zis = new ZipInputStream(new BufferedInputStream(new FileInputStream(fileName)));
            
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                String entryName = entry.getName();

                // content file
                if (entryName.endsWith(CONTENT_FILE)) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("parse() content file extracting: " + entryName);
                    }

                    BufferedOutputStream dest = null;
                    try {
                        dest = new BufferedOutputStream(new FileOutputStream(tempFile), BUFFER);

                        while ((count = zis.read(data, 0, BUFFER)) != -1) {
                            dest.write(data, 0, count);
                        }

                        dest.flush();
                    }
                    finally {
                        try {
                            if (dest != null) {
                                dest.close();
                            }
                        }
                        catch (IOException ioe) {
                            logger.fatal("parse() can't close BufferedOutputStream", ioe);
                        }
                    }

                    dest.close();
                }
                // meta file
                else if (entryName.endsWith(META_FILE)) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("parse() meta file extracting: " + entryName);
                    }

                    BufferedOutputStream dest = null;
                    try {
                        dest = new BufferedOutputStream(new FileOutputStream(metaFile), BUFFER);

                        while ((count = zis.read(data, 0, BUFFER)) != -1) {
                            dest.write(data, 0, count);
                        }

                        dest.flush();
                    }
                    finally {
                        try {
                            if (dest != null) {
                                dest.close();
                            }
                        }
                        catch (IOException ioe) {
                            logger.fatal("parse() can't close BufferedOutputStream", ioe);
                        }
                        
                    }
                }
                // other file
                else {
                    if (logger.isDebugEnabled()) {
                        logger.debug("parse() zip entry: " + entryName);
                    }
                }
            }
        } catch (IOException ioe) {
            logger.fatal("parse() failed with IOException", ioe);
            throw ioe;
        } finally {
            try {
                if (zis != null) {
                    zis.close();
                }
            } catch (IOException ioe) {
                logger.fatal("parse() can't close ZipInputStream", ioe);
            }
            
        }
    }
}
