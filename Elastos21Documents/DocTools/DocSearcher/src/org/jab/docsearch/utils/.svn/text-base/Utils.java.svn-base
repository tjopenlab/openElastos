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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.log4j.Logger;

import org.jab.docsearch.constants.OSType;
import org.jab.docsearch.spider.SpiderUrl;

/**
 * This utility class primarily performs string manipulation functions.
 * 
 * @version $Id: Utils.java,v 1.17 2006/08/16 19:48:46 henschel Exp $
 */
public final class Utils {
    /**
     * Log4J
     */
    private final static Logger logger = Logger.getLogger(Utils.class.getName());
    private final static String PATH_SEPARATOR = FileUtils.PATH_SEPARATOR;
    public final static String LINE_SEPARATOR = System.getProperty("line.separator");


    /**
     * Replace String
     *
     * @param s   search string
     * @param s1  string
     * @param s2  replace string  
     * @return    a string where s has been replaced with s2 given a string s1
     */
    public static String replaceAll(String s, String s1, String s2) {
        while (s1.indexOf(s) != -1) {
            int i = s1.indexOf(s);
            if (i >= 1) {
                s1 = s1.substring(0, i) + s2 + s1.substring(i + s.length(), s1.length());
            } else if (i == 0) {
                s1 = s2 + s1.substring(i + s.length(), s1.length());
            }
        }
        return s1;
    }


    public static double getAverageSearchScore(ArrayList loggedSearches) {
        int numIs = loggedSearches.size();
        double returnD = 0.0;
        double totalD = 0.0;
        double temD = 0.0;
        LogSearch ls;
        if (numIs > 0) {
            Iterator it = loggedSearches.iterator();
            while (it.hasNext()) {
                ls = (LogSearch) it.next();
                temD = ls.score;
                totalD += temD;
            } // end while
            if (totalD > 0.0)
                returnD = totalD / numIs;
        }
        return returnD;
    } // end for getAverageSearchScore


    public static boolean hasUser(String toMatch, ArrayList listing) {
        int numUs = listing.size();
        boolean returnB = false;
        if (numUs > 0) {
            String temC = "";
            Iterator it = listing.iterator();
            while (it.hasNext()) {
                temC = (String) it.next();
                if (temC.equals(toMatch)) {
                    returnB = true;
                    break;
                }
            } // end while
        } // end has users
        return returnB;
    } // end foir hasUserBool


    /**
     * @return true if a URL ends with a slash
     */
    public static boolean endsWithSlash(String toCkeck) {
        boolean retB = false;
        if ((toCkeck.endsWith("/")) || (toCkeck.endsWith("\\")))
            retB = true;
        return retB;
    }


    /**
     * @return url given a filename and the text to find (match) and replace it
     *         with
     */
    public static String getURL(String fileName, String match, String replace) {
        String returnString = "";
        returnString = replace + fileName.substring(match.length(), fileName.length());
        returnString = Utils.replaceAll("\\", returnString, "/");

        // System.out.println("Converted file("+fileName+") to
        // "+returnString+"\nmatch:"+match+"\nreplace:"+replace);
        return returnString;
    }


    /**
     * @return number of slashes (/) in a URL
     */
    public static int countSlash(String URLtoCount) {
        int returnInt = 0;
        int totalLen = URLtoCount.length();
        int startSpot = URLtoCount.indexOf(PATH_SEPARATOR);
        if (startSpot != -1) {
            returnInt++;
            do {
                startSpot++;
                if (startSpot > totalLen) {
                    break;
                }

                startSpot = URLtoCount.indexOf(PATH_SEPARATOR, startSpot);
                if (startSpot == -1) {
                    break;
                }

                returnInt++;

                // System.out.println("Found slash");
            } while (startSpot != -1);
        }

        return returnInt;
    }


    /**
     * @return the number of rows in a html file containing an html table
     */
    public static int getNumObjectRows(String fileName) {
        int returnInt = 0;
        // load file and count <tr tags
        try {
            File origFile = new File(fileName);
            if (origFile.exists()) {
                FileInputStream fi = new FileInputStream(origFile);
                int curI = 0; // reset i
                char curChar = ' ';
                char lastChar = ' ';
                char nextToLastChar = ' ';
                StringBuffer rowString;
                while (curI != -1) {
                    curI = fi.read();
                    if (curI != -1) {
                        //
                        lastChar = nextToLastChar;
                        nextToLastChar = curChar;
                        curChar = (char) curI;
                        rowString = new StringBuffer();
                        rowString.append(lastChar);
                        rowString.append(nextToLastChar);
                        rowString.append(curChar);
                        if (rowString.toString().toLowerCase().equals("<tr"))
                            returnInt++;
                    } // curI!=-1
                    else
                        break;
                }
                fi.close();
            } // end for file exists
            else
                returnInt = -1;
        } // end of trying
        catch (Exception eF) {
            returnInt = 0;
        }
        return returnInt;
    } // end for getNumObjectRows


    /**
     * Method returns the filename with out parent directories
     *
     * @param fileString  fileString
     * @return            a filename without its parent directory included in the name
     */
    public static String getNameOnly(String fileString) {
        if (fileString == null) {
            return null;
        }

        // remove parent objects
        if (fileString.indexOf(PATH_SEPARATOR) != -1) {
            return fileString.substring(fileString.lastIndexOf(PATH_SEPARATOR) + 1, fileString.length());
        }
        else if (fileString.indexOf("\\") != -1) {
            return fileString.substring(fileString.lastIndexOf("\\") + 1, fileString.length());
        }
        else if (fileString.indexOf("/") != -1) {
            return fileString.substring(fileString.lastIndexOf("/") + 1, fileString.length());
        }
        else {
            return fileString;
        }
    }


    /**
     * @return parent folder for a file named in fileString
     */
    public static String getFolderOnly(String fileString) {
        if (fileString.indexOf(PATH_SEPARATOR) != -1)
            return fileString.substring(0, fileString.lastIndexOf(PATH_SEPARATOR));
        else if (fileString.indexOf("\\") != -1)
            return fileString.substring(0, fileString.lastIndexOf("\\"));
        else if (fileString.indexOf("/") != -1)
            return fileString.substring(0, fileString.lastIndexOf("/"));
        else
            return "";
    }


    /**
     * Gets OS type
     *
     * @see OSType
     * @return  OSType number
     */
    public static int getOSType() {
        String os = System.getProperty("os.name").toLowerCase();

        if (os.indexOf("linux") != -1) {
            return OSType.LINUX;
        }
        else if (os.indexOf("windows") != -1) {
            return OSType.WIN_32;
        }
        else if (os.indexOf("nix") != -1) {
            return OSType.UNIX;
        }
        else if (os.indexOf("mac") != -1) {
            return OSType.MAC;
        }
        else {
            return OSType.UNKNOWN;
        }
    }


    public static String escapeSpaces(String toEsc) {
        StringBuffer returnBuf = new StringBuffer();
        int sizeS = toEsc.length();
        char cr = ' ';
        for (int i = 0; i < sizeS; i++) {
            cr = toEsc.charAt(i);
            if (cr == ' ')
                returnBuf.append("\\ ");
            else
                returnBuf.append(cr);
        }
        return returnBuf.toString();
    } // end for escape spaces


    /**
     * Gets user home
     *
     * @param osNum
     * @param defaultOsUserHome
     * @return                   users home directory - varies by platform
     */
    public static String getUserHome(int osNum, String defaultOsUserHome) {
        String returnString = defaultOsUserHome;

        switch (osNum) {
            case OSType.WIN_32: {
                String tempHome = Messages.getString("win32.home");
                if (tempHome.equals("$HOME")) {
                    returnString = System.getProperty("user.home");
                }
                else if (tempHome.equals(".")) {
                    returnString = System.getProperty("user.dir");
                }
                break;
            }
            case OSType.LINUX: {
                String tempHome = Messages.getString("lin.home");
                if (tempHome.equals("$HOME")) {
                    returnString = System.getProperty("user.home");
                }
                else if (tempHome.equals(".")) {
                    returnString = System.getProperty("user.dir");
                }
                break;
            }
            case OSType.UNIX: {
                returnString = System.getProperty("user.dir");
                break;
            }
            case OSType.MAC: {
                returnString = System.getProperty("user.dir");
                break;
            }
            default: { // don't know what it is
                returnString = System.getProperty("user.dir");
                break;
            }
        }

        logger.log(NoticeLevel.NOTICE, "getUserHome() using HOME directory=" + returnString);

        return returnString;
    }


    /**
     * Gets CDROM directory
     *
     * @return path to a CD ROM - varies depending on the platform
     */
    public static String getCDROMDir(int osNum) {
        if (logger.isDebugEnabled()) {
            logger.debug("getCDROMDir('" + osNum + "')");
        }

        String tempCdDir = System.getProperty("user.dir");
        if (! tempCdDir.equals("")) {
            File testFile = new File(tempCdDir);
            if (testFile.exists()) {
                logger.info("getCDROMDir() CDROM Dir: " + tempCdDir);
                return tempCdDir;
            }
            else {
                logger.error("getCDROMDir() NO CDROM DIR FOUND... ");
                return "";
            }
        }
        else {
            logger.info("getCDROMDir() NO CDROM DIR FOUND... ");
            return "";
        }
    }


    /**
     * @return a concatenated string of to 37 chars in length- stips of the
     *         beginning
     */
    public static String concatStr(String toConcat) {
        if (toConcat.length() > 37)
            return "~" + toConcat.substring(toConcat.length() - 37, toConcat.length());
        else
            return toConcat;
    } // end for concat


    /**
     * @return a concatenated string of the specified length in chars - stips of
     *         the ending
     */
    public static String concatStrTo(String toConcat, int len) {
        if (toConcat.length() > len)
            return "~" + toConcat.substring(toConcat.length() - len, toConcat.length());
        else
            return toConcat;
    } // end for concat


    /**
     * @return a concatenated string of the specified length in chars - stips of
     *         the beginning
     */
    public static String concatStrToEnd(String toConcat, int len) {
        if (toConcat.length() > len)
            return toConcat.substring(0, len) + "...";
        else
            return toConcat;
    } // end for concat


    /**
     * Looks for tag attribute in tag
     *
     * @param toLookFor
     * @param toLookIn
     * @return attribute from the text of an html tag...
     */
    public static String getTagString(String toLookFor, String toLookIn) {
        String toLookInLower = toLookIn.toLowerCase();

        if (toLookInLower.indexOf(toLookFor) == -1) {
            return "";
        }
        else {
            boolean firstQFnd = true;
            StringBuffer tempS = new StringBuffer();
            int endPos = toLookIn.length();
            int startPos = toLookInLower.indexOf(toLookFor) + toLookFor.length();

            for (int i = startPos; i < endPos; i++) {
                char tC = toLookIn.charAt(i);
                if (toLookIn.charAt(i) == '"') {
                    if (! firstQFnd) {
                        break;
                    }
                    else {
                        firstQFnd = false;
                    }
                }
                else if (toLookIn.charAt(i) == '>') {
                    break;
                }
                else {
                    tempS.append(tC);
                }
            }

            if (tempS.toString().trim().equals("")) {
                return "";
            }
            else {
                return tempS.toString();
            }
        }
    }


    /**
     * @return value from a key in a line of properties style text
     */
    public static String getLineParam(String keyToFind, String lineToSearch) {
        String returnString = "";
        // iterate over chars....
        int numCharsTotal = lineToSearch.length();
        StringBuffer curVal = new StringBuffer();
        char cu = ' ';
        int keyLocaion = lineToSearch.indexOf(keyToFind);
        if (keyLocaion != -1) {
            for (int i = keyLocaion + 1 + keyToFind.length(); i < numCharsTotal; i++) {
                cu = lineToSearch.charAt(i);
                if ((cu == '\n') || (cu == '\r'))
                    break;
                else
                    curVal.append(cu);
            }
            returnString = curVal.toString();
        } // end for has key
        return returnString;
    } // end for getLineParam


    /**
     * @return text given some HTML --- strips out markup
     */
    public static String nonTagText(String removeStr) {
        StringBuffer retBuf = new StringBuffer();
        int strLen = removeStr.length();
        boolean inTag = false;
        char curChar = ' ';
        for (int i = 0; i < strLen; i++) {
            curChar = removeStr.charAt(i);
            if (curChar == '<')
                inTag = true;
            else if (curChar == '>') {
                retBuf.append(" ");
                inTag = false;
            }
            if ((!inTag) && (curChar != '>'))
                retBuf.append(curChar);
            else if ((!inTag) && (curChar == '>'))
                retBuf.append(" ");
        } // end for string
        return retBuf.toString();
    } // end for nonTagText


    /**
     * Gets domain from  URL
     *
     * @param  url  URL
     * @return      website name of a web page given a url
     */
    public static String getDomainUrl(String url) {
        int slashCount = 0;
        for (int i = 0; i < url.length(); i++) {
            if (url.charAt(i) == '/') {
                slashCount++;
                if (slashCount == 3) {
                    return url.substring(0, i +1);
                }
            }
        }

        // here no third slash found
        if (slashCount == 2) {
            return url + '/';
        }

        logger.warn("getDomainUrl() couldn't retrieve domain from: " + url);
        
        return "";
    }


    /**
     * @return fully qualified URL from a relative hyperlink in a web page
     *         specified by baseUrl
     */
    public static String getRealUrl(String link, String baseUrl) {
        String returnS = "";
        String domainUrl = Utils.getDomainUrl(baseUrl);
        int anchorPos = link.indexOf("#");
        if (anchorPos != -1)
            link = link.substring(0, anchorPos);
        // DETERMINE THE BASE URL
        if (baseUrl.endsWith("/")) {
            baseUrl = baseUrl.substring(0, baseUrl.length() - 1);
        }
        if (link.startsWith("http")) {
            returnS = link;
        }
        else if (link.indexOf("/") == -1) {
            returnS = baseUrl + "/" + link;
        }
        else if (link.startsWith("/")) {
            returnS = domainUrl + link;
        }
        else if (link.indexOf("../") == -1) {
            returnS = baseUrl + "/" + link;
        }

        if (returnS.equals("")) {
            logger.error("getRealUrl() Failed to construct full URL from link:" + link + "\nFound on page:" + baseUrl);
        }
        return returnS;
    }


    /**
     * Convert HTML entities to their text equivalents
     * 
     * @param link  link
     * @return      url with HTML entities converted to their text equivalents
     */
    public static String getNormalUrl(String link) {
        link = Utils.replaceAll("&amp;", link, "&");
        link = Utils.replaceAll("%2B", link, "+");
        link = Utils.replaceAll("%2F", link, "/");
        link = Utils.replaceAll("%2f", link, "/");
        link = Utils.replaceAll("%2C", link, ",");
        link = Utils.replaceAll("%22", link, "\"");
        link = Utils.replaceAll("%23", link, "#");
        link = Utils.replaceAll("%24", link, "$");
        link = Utils.replaceAll("%3A", link, ":");
        link = Utils.replaceAll("%25", link, "%");
        link = Utils.replaceAll("+", link, " ");
        link = Utils.replaceAll("%26", link, "&");
        link = Utils.replaceAll("%27", link, "'");
        link = Utils.replaceAll("%20", link, " ");
        link = Utils.replaceAll("%28", link, "(");
        link = Utils.replaceAll("%29", link, ")");
        link = Utils.replaceAll("%5E", link, "^");
        link = Utils.replaceAll("%3f", link, "?");
        link = Utils.replaceAll("|", link, "%7C");
        return link;
    }


    /**
     * @return text concatenated to a specified size
     */
    public static String concatEnd(String toShorten, int size) {
        String returnString = "";
        int comS = toShorten.length();
        if (comS > size) {
            returnString = "..." + toShorten.substring(comS - size, comS);
        } else
            returnString = toShorten;
        return returnString;
    } // end of concat


    /**
     * @return parent folder for a URL
     */
    public static String getBaseUrlFolder(String toGetFrom) {
        String returnString = toGetFrom;
        if (!toGetFrom.endsWith("/")) {
            int lastSpot = toGetFrom.lastIndexOf("/");
            if (lastSpot != -1) {
                returnString = returnString.substring(0, lastSpot);
                logger.debug("getBaseUrlFolder() Requiring BASE URL : " + returnString);
            } else
                returnString = "";
        } else
            returnString = toGetFrom;
        return returnString;
    }


    /**
     * Gets all SpiderLinks from file
     *
     * @param  filename
     * @return           an ArrayList of SpiderUrls for links in a downloaded file
     */
    public static ArrayList getSpiderLinks(String filename) {
        ArrayList spiderList = new ArrayList();

        if (filename == null) {
            logger.warn("getSpiderLinks() filename is null");
            return spiderList;
        }

        BufferedReader reader = null;
        try {
            File loadFile = new File(filename);
            if (! loadFile.exists()) {
                logger.warn("getSpiderLinks() Spider URL file does not exist " + filename);
            }
            else {
                reader = new BufferedReader(new FileReader(loadFile));
                
                String line;
                while ((line = reader.readLine()) != null) {
                    SpiderUrl tempUrl = new SpiderUrl(line);
                    spiderList.add(tempUrl);
                }
            }
        }
        catch (IOException ioe) {
            logger.error("getSpiderLinks() Error loading spider url links from file " + filename, ioe);
        }
        finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("getSpiderLinks() can't close BufferedReader");
            }
        }

        // return the arraylist of spider url objects
        return spiderList;
    }


    /**
     * @return text with html entities in place of the and sign and greater than
     *         and less than signs
     */
    public static String convertTextToHTML(String conv) {
        String returnString = conv;
        // lowerCase
        returnString = Utils.replaceAll("& ", returnString, "&amp; "); // and
        // symbol
        returnString = Utils.replaceAll("\n", returnString, "&nbsp;"); // spacer
        returnString = Utils.replaceAll("<", returnString, "&lt;"); // less than
        returnString = Utils.replaceAll(">", returnString, "&gt;"); // greater
        // than
        returnString = Utils.replaceAll("\"", returnString, "&quot;"); // quot
        return returnString;
    }


    public static String getPercentFromFloat(double aDouble) {
        String returnString = "";
        double newDouble = 100.0 * aDouble;
        String tempString = "" + newDouble;
        int tempLen = tempString.length();
        StringBuffer newSb = new StringBuffer();
        char curChar = ' ';
        int pastDot = 0;
        boolean foundDot = false;
        for (int i = 0; i < tempLen; i++) {
            curChar = tempString.charAt(i);
            if (curChar == '.') {
                foundDot = true;
            } else if (foundDot) {
                pastDot++;
            }
            newSb.append(curChar);
            if (pastDot >= 1) {
                newSb.append(" %");

                break;
            }
        }
        returnString = newSb.toString();
        return returnString;
    }


    public static String getChangeFromFloat(double aDouble) {
        String returnString = "";
        String tempString = "" + aDouble;
        int tempLen = tempString.length();
        StringBuffer newSb = new StringBuffer();
        char curChar = ' ';
        int pastDot = 0;
        boolean foundDot = false;
        for (int i = 0; i < tempLen; i++) {
            curChar = tempString.charAt(i);
            if (curChar == '.') {
                foundDot = true;
            }
            else if (foundDot) {
                pastDot++;
            }

            newSb.append(curChar);
            if (pastDot >= 1) {
                break;
            }
        }

        returnString = newSb.toString();

        return returnString;
    }


    /**
     * Get values in kilo format
     * TODO rewrite method, also with mega byte and locale for Mo for France!! update also all references
     *
     * @param toGet
     * @return
     */
    public static String getKStyle(String toGet) {
        String returnString = null;

        try {
            double l = Double.parseDouble(toGet);
            double newD = l / 1024.0;
            returnString = getChangeFromFloat(newD) + " k";
        }
        catch (Exception eN) {
            returnString = toGet;
        }

        return returnString;
    }

}
