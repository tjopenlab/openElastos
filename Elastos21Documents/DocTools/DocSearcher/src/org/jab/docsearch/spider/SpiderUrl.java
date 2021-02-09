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
package org.jab.docsearch.spider;

import org.apache.log4j.Logger;

import org.jab.docsearch.utils.Utils;

/**
 * Class SpiderUrl
 * 
 * @version $Id: SpiderUrl.java,v 1.3 2005/10/09 18:03:07 henschel Exp $
 */
public final class SpiderUrl {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    private String href = "";
    private boolean isSpidered = false;
    private boolean isDeadlink = false;
    private String contentType = "UNKNOWN";
    private String errorCode = "";
    private long lastModified = 0;
    private long size = 0;
    private String md5 = "";
    private int indexLocation = -1;


    /**
     * Constructor
     *
     * @param href
     */
    public SpiderUrl(String href) {
        if (href.indexOf("|") == -1) {
            this.href = href;
        }
        else {
            // loads each value seperated by a "|"
            int curPart = 0;
            int lineLen = href.length();
            long tmpVl = 0;
            StringBuffer tempVl = new StringBuffer();
            for (int i = 0; i < lineLen; i++) {
                char c = href.charAt(i);
                if ((c == '|') || (i == lineLen - 1)) {
                    if (i == lineLen - 1) {
                        tempVl.append(c);
                    }

                    switch (curPart) {
                        case 0: // href
                            this.href = Utils.replaceAll("%7C", tempVl.toString(), "|");
                            break;
                        case 1: // time
                            try {
                                tmpVl = Long.parseLong(tempVl.toString());
                                this.lastModified = tmpVl;
                            }
                            catch (NumberFormatException nfe) {
                                logger.error("SpiderUrl() failed", nfe);
                            }
                            break;
                        case 2: // size
                            try {
                                tmpVl = Long.parseLong(tempVl.toString());
                                this.size = tmpVl;
                            } catch (Exception eR) {
                                eR.printStackTrace();
                            }
                            break;
                        case 3: // type
                            this.contentType = tempVl.toString();
                            break;
                        default: // md5
                            this.md5 = tempVl.toString();
                            break;
                    }
                    curPart++;
                    tempVl = new StringBuffer();
                }
                else {
                    tempVl.append(c);
                }
            }
        }
    }


    /**
     * Sets MD5
     *
     * @param md5
     */
    public void setMd5(String md5) {
        this.md5 = md5;
    }


    /**
     * Gets MD5
     *
     * @return
     */
    public String getMd5() {
        return md5;
    }


    /**
     * Gets URL
     *
     * @return
     */
    public String getUrl() {
        return Utils.replaceAll("%7C", href, "|");
    }


    /**
     * Gets is spidered
     *
     * @return
     */
    public boolean getIsSpidered() {
        return isSpidered;
    }


    /**
     * Sets is spidered
     *
     * @param isSpiderd
     */
    public void setSpidered(boolean isSpidered) {
        this.isSpidered = isSpidered;
    }


    /**
     * Gets is deas link
     *
     * @return
     */
    public boolean getIsDeadLink() {
        return isDeadlink;
    }


    /**
     * Sets is dead link
     *
     * @param isDeadlink
     */
    public void setIsDeadLink(boolean isDeadlink) {
        this.isDeadlink = isDeadlink;
    }


    /**
     * Gets error code
     *
     * @return
     */
    public String getErrorCode() {
        return errorCode;
    }


    /**
     * Sets error code
     *
     * @param errorCode
     */
    public void setErrCode(String errorCode) {
        this.errorCode = errorCode;
    }


    /**
     * Sets last modified
     * @param lastModified
     */
    public void setLastModified(long lastModified) {
        this.lastModified = lastModified;
    }


    /**
     * Gets last modified
     *
     * @return
     */
    public long getLastModified() {
        return lastModified;
    }


    /**
     * Sets size
     *
     * @param size
     */
    public void setSize(long size) {
        this.size = size;
    }


    /**
     * Gets size
     *
     * @return
     */
    public long getSize() {
        return size;
    }


    /**
     * Sets content type
     *
     * @param contentType
     */
    public void setContentType(String contentType) {
        this.contentType = contentType;
    }


    /**
     * Gets content type
     *
     * @return
     */
    public String getContentType() {
        return contentType;
    }


    /**
     * Sets index location
     *
     * @param indexLocation
     */
    public void setIndexLocation(int indexLocation) {
        this.indexLocation = indexLocation;
    }


    /**
     * Gets index location
     *
     * @return
     */
    public int getIndexLocation() {
        return indexLocation;
    }
}
