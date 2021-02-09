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
package org.jab.docsearch.utils;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

import org.apache.log4j.Logger;

import org.jab.docsearch.spider.SpiderUrl;

/**
 * This class contains useful methods for network
 * 
 * @version $Id: NetUtils.java,v 1.1 2005/10/11 21:04:38 henschel Exp $
 */
public final class NetUtils {
    /**
     * Log4J
     */
    private final static Logger logger = Logger.getLogger(NetUtils.class.getName());
    /**
     * DocSearcher user agent
     */
    private final static String USER_AGENT = "DocSearcher " + Messages.getString("DocSearch.version");
    
    
    /**
     * Gets URL size (content)
     *
     * @param url  URL for connect
     * @return     size in bytes of a url or 0 if broken or timed out connection
     */
    public static long getURLSize(String url) {
        try {
            URL tmpURL = new URL(url);
            URLConnection conn = tmpURL.openConnection();

            // set connection parameter
            conn.setDoInput(true);
            conn.setDoOutput(false);
            conn.setUseCaches(false);
            conn.setRequestProperty("User-Agent", USER_AGENT);

            // connect
            conn.connect();

            long contentLength = conn.getContentLength();

            if (logger.isDebugEnabled()) {
                logger.debug("getURLSize() content lentgh=" + contentLength + " of URL='" + url + "'");
            }

            return contentLength;
        }
        catch (IOException ioe) {
            logger.error("getURLSize() failed for URL='" + url + "'", ioe);
            return 0;
        }
    }


    /**
     * Gets URL modified date as long
     *
     * @param url  URL to connect
     * @return         date of URLs modification or 0 if an error occurs
     */
    public static long getURLModifiedDate(String url) {
        try {
            URL tmpURL = new URL(url);
            URLConnection conn = tmpURL.openConnection();

            // set connection parameter
            conn.setDoInput(true);
            conn.setDoOutput(false);
            conn.setUseCaches(false);
            conn.setRequestProperty("User-Agent", USER_AGENT);

            // connect
            conn.connect();

            long modifiedDate = conn.getLastModified();

            if (logger.isDebugEnabled()) {
                logger.debug("getURLSize() modified date=" + modifiedDate + " of URL='" + url + "'");
            }

            return modifiedDate;
        }
        catch (IOException ioe) {
            logger.error("getURLModifiedDate() failed for URL='" + url + "'", ioe);
            return 0;
        }
    }


    /**
     * Downloads URL to file
     *
     * @param url   URL for download
     * @param file  URL content downloads to to this file
     * @return      true if URL successfully downloads to a file
     */
    public static boolean downloadURLToFile(String url, String file) {
        BufferedInputStream inputStream = null;
        BufferedOutputStream outputStream = null;
        try {
            // if the file downloads - save it and return true
            URL tmpURL = new URL(url);
            URLConnection conn = tmpURL.openConnection();

            // set connection parameter
            conn.setDoInput(true);
            conn.setDoOutput(false);
            conn.setUseCaches(false);
            conn.setRequestProperty("User-Agent", USER_AGENT);

            // connect
            conn.connect();

            // open streams
            inputStream = new BufferedInputStream(conn.getInputStream());
            outputStream = new BufferedOutputStream(new FileOutputStream(file));

            // copy data from URL to file
            int readed = 0;
            while ((readed = inputStream.read()) != -1) {
                outputStream.write(readed);
            }

            return true;
        }
        catch (IOException ioe) {
            logger.fatal("downloadURLToFile() failed for URL='" + url + "'", ioe);
            return false;
        }
        finally {
            try {
                if (outputStream != null) {
                    outputStream.close();
                }
            } catch (IOException ioe) {
                logger.fatal("downloadURLToFile() can't close BufferedOutputStream", ioe);
            }

            try {
                if (inputStream != null) {
                    inputStream.close();
                }
            } catch (IOException ioe) {
                logger.fatal("downloadURLToFile() can't close BufferedInputStream", ioe);
            }
        }
    }


    /**
     * Get SpiderUrl status
     *
     * @param URL   URL
     * @param file  URL content downloads to to this file
     * @return          -1 if link is broken, 0 if the file is unchanged or 1 if the file
     *                  is different... part of caching algoritm.
     */
    public static int getURLStatus(SpiderUrl spiderURL, String file) {
        // -1 means broken link
        //  0 means same file
        //  1 means changed

        int status = -1;
        
        try {
            // attempt to obtain status from date
            URL url = new URL(spiderURL.getUrl());
            URLConnection conn = url.openConnection();

            // set connection parameter
            conn.setDoInput(true);
            conn.setDoOutput(false);
            conn.setUseCaches(false);
            conn.setRequestProperty("User-Agent", USER_AGENT);

            // connect
            conn.connect();

            // check date
            long compareDate = spiderURL.getLastModified();
            long urlDate = conn.getLastModified();

            if (compareDate == urlDate && urlDate != 0) {
                // the file is not changed
                status = 0;
            }
            else if (compareDate != urlDate && compareDate != 0 && urlDate != 0) {
                // the file is changed
                status = 1;
            }
            else {
                // download the URL and compare hashes
                boolean downloaded = downloadURLToFile(spiderURL.getUrl(), file);
                if (downloaded) {
                    // download ok
                    
                    // compare file hashes
                    String compHash = FileUtils.getMD5Sum(file);

                    if (compHash.equals(spiderURL.getMd5())) {
                        // same
                        status = 0;
                    }
                    else {
                        // changed
                        status = 1;
                    }
                }
                else {
                    // download failed
                    
                    // broken link
                    status = -1;
                }
            }
        }
        catch (IOException ioe) {
            logger.error("getURLStatus() failed for URL='" + spiderURL.getUrl() + "'", ioe);
            status = -1;
        }

        return status;
    }
}
