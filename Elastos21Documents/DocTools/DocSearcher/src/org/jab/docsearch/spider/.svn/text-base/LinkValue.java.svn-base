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
 * Class LinkValue
 * 
 * @version $Id: LinkValue.java,v 1.3 2005/10/09 18:03:07 henschel Exp $
 */
public final class LinkValue {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    private String href;
    private String page;
    private String realLink;
    private boolean convertedLink = false;


    /**
     * Constructor
     *
     * @param page
     * @param href
     */
    protected LinkValue(String page, String href) {
        this.href = href;
        if (href.indexOf("#") != -1) {
            int anchorPos = href.indexOf("#");
            href = href.substring(0, anchorPos);
        }
        this.page = page;
    }


    /**
     * Gets real link
     *
     * @return  real link
     */
    protected String getRealLink() {

        logger.debug("getRealLink() page='" + page + "' href='" + href + "'");
        
        if (convertedLink) {
            return realLink;
        }
        else {
            String lowerRef = href.toLowerCase();
            String domainUrl = Utils.getDomainUrl(page);
            int domLen = domainUrl.length();
            
            String pageFold = page;
            if (! page.endsWith("/")) {
                pageFold = page.substring(0, page.lastIndexOf("/") + 1);
                // System.out.println("page folder is"+pageFold);
            }
            else {
                pageFold = page;
            }

            // check for full link
            if (lowerRef.startsWith("http")) {
                convertedLink = true;
                realLink = href;
            }
            else {
                // check link started with /
                if (lowerRef.startsWith("/")) {
                    // go up to root and make rel link
                    realLink = domainUrl + href.substring(1, href.length());
                }
                // check link started with ./
                else if (lowerRef.startsWith("./")) {
                    realLink = pageFold + href.substring(2, href.length());
                }
                // check link started with ../
                else if (lowerRef.startsWith("../")) {
                    // go up a folder - or so to make rel link
                    boolean folderFound = false;
                    String newFolder = pageFold;
                    String dotPoint = href;
                    int lastSlash = 0;
                    if (newFolder.endsWith("/")) {
                        lastSlash = newFolder.lastIndexOf("/");
                        newFolder = newFolder.substring(0, lastSlash);
                    }
                    do {
                        if (dotPoint.startsWith("../")) {
                            dotPoint = dotPoint.substring(3, dotPoint.length());
                        }
                        else {
                            folderFound = true;
                            break;
                        }
                        lastSlash = newFolder.lastIndexOf("/");
                        if (lastSlash != -1 && newFolder.length() > domLen) {
                            newFolder = newFolder.substring(0, lastSlash);
                        }
                        else {
                            folderFound = true;
                            break;
                        }
                    }
                    while (! folderFound);

                    realLink = newFolder + '/' + dotPoint;
                }
                else {
                    // assume rel link at page location
                    if (! pageFold.endsWith("/")) {
                        realLink = pageFold + "/" + href;
                    }
                    else {
                        realLink = pageFold + href;
                    }
                }
            } // end for not a full link

            logger.debug("getRealLink() real link='" + realLink + "' pagefold='" + pageFold + "'");
            
            convertedLink = true;
            return realLink;
        }
    }
}
