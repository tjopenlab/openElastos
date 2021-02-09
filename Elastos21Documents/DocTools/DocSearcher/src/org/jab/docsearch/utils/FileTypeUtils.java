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

import org.apache.log4j.Logger;

import org.jab.docsearch.constants.FileType;

/**
 * File type utils 
 * 
 * @version $Id: FileTypeUtils.java,v 1.3 2006/08/16 19:48:46 henschel Exp $
 */
public final class FileTypeUtils {
    /**
     * Log4J
     */
    private final static Logger logger = Logger.getLogger(Utils.class.getName());


    /**
     * Checks file is text codument
     * 
     * @param file  filename
     * @return      true for file ending in .java, .txt, .ini, etc...
     */
    public static boolean isFileTypeText(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".java")
                || lowerFile.endsWith(".txt")
                || lowerFile.endsWith(".ini")) {
            return true;            
        }

        return false;
    }


    /**
     * Check file is RTF document
     *
     * @param file  filename
     * @return      true for file ending in rtf
     */
    /*public static boolean isFileTypeRTF(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".rtf")) {
            return true;
        }

        return false;
    }*/


    /**
     * Checks file is MS Word document
     *
     * @param file  filename
     * @return      true for file ending in .doc
     */
    /*public static boolean isFileTypeMSWord(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".doc")) {
            return true;
        }

        return false;
    }*/


    /**
     * Checks file is MS Excel document
     *
     * @param file  filename
     * @return      true for links ending in .xls
     */
    /*public static boolean isFileTypeMSExcel(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".xls")) {
            return true;
        }

        return false;
    }*/


    /**
     * Checks file is PDF document
     *
     * @param file  filename
     * @return      true for file ending in .pdf
     */
    /*public static boolean isFileTypePDF(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".pdf")) {
            return true;
        }

        return false;
    }*/


    /**
     * Check file is OpenOffice document
     *
     * @param file  filename
     * @return      true for links ending in .sxw, .sxi, .sxp, .sxd, etc...
     */
    /*public static boolean isFileTypeOO(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".sxw")
                || lowerFile.endsWith(".sxc")
                || lowerFile.endsWith(".sxi")
                || lowerFile.endsWith(".sxp")
                || lowerFile.endsWith(".sxd")) {
            return true;
        }

        return false;
    }*/


    /**
     * Checks is filetype viewable
     *
     * @param file  filename
     * @return      true for file ending in .htm, .shtm, .asp, .jsp, etc...
     */
    /*public static boolean isFileTypeViewable(String file) {
        String lowerLink = file.toLowerCase();

        if (lowerLink.endsWith(".htm")
                || lowerLink.endsWith(".html")
                || lowerLink.endsWith(".shtm")
                || lowerLink.endsWith(".shtml")
                || lowerLink.endsWith(".php")
                || lowerLink.endsWith(".asp")
                || lowerLink.endsWith(".txt")
                || lowerLink.endsWith(".rtf")
                || lowerLink.endsWith(".java")
                || lowerLink.endsWith("/")
                || lowerLink.endsWith(".mil/")
                || lowerLink.endsWith(".exe")
                || lowerLink.endsWith(".sh")
                || lowerLink.endsWith(".org/")
                || lowerLink.endsWith(".jsp")) {
            return true;
        }

        return false;
    }*/


    /**
     * Checks is filetype HTML
     *
     * @param file  filename
     * @return      true for links ending in .htm, .shtm, .asp, .jsp, etc...
     */
    public static boolean isFileTypeHTML(String file) {
        String lowerFile = file.toLowerCase();

        if (lowerFile.endsWith(".htm")
                || lowerFile.endsWith(".html")
                || lowerFile.endsWith(".shtm")
                || lowerFile.endsWith(".shtml")
                || lowerFile.endsWith(".php")
                || lowerFile.endsWith(".asp")
                || lowerFile.endsWith(".jsp")) {
            return true;
        }

        return false;
    }


    /**
     * Method returns the filetype as int
     * 
     * @param file  filename 
     * @return      filetype as int
     * @see         org.jab.docsearch.constants.FileType
     */
    public static int getFileType(String file) {
        String lowerFile = file.toLowerCase();
        
        // HTML
        if ("html".equals(lowerFile)
                || "htm".equals(lowerFile)
                || "shtml".equals(lowerFile)
                || "shtm".equals(lowerFile)
                || "php".equals(lowerFile)
                || "asp".equals(lowerFile)
                || "jsp".equals(lowerFile)) {
            return FileType.HTML;
        }
        // TEXT
        else if ("txt".equals(lowerFile)) {
            return FileType.TEXT;
        }
        // MS Word
        else if ("doc".equals(lowerFile)) {
            return FileType.MS_WORD;
        }
        // MS Excel
        else if ("xls".equals(lowerFile)) {
            return FileType.MS_EXCEL;
        }
        // PDF
        else if ("pdf".equals(lowerFile)) {
            return FileType.PDF;
        }
        // RTF
        else if ("rtf".equals(lowerFile)) {
            return FileType.RTF;
        }
        // OO Writer
        else if ("sxw".equals(lowerFile)) {
            return FileType.OO_WRITER;
        }
        // OO Impress
        else if ("sxi".equals(lowerFile)
                || "sxp".equals(lowerFile)) {
            return FileType.OO_IMPRESS;
        }
        // OO Calc
        else if ("sxc".equals(lowerFile)) {
            return FileType.OO_CALC;
        }
        // OO Draw
        else if ("sxd".equals(lowerFile)) {
            return FileType.OO_DRAW;
        }
        // OpenDocument Text
        else if ("odt".equals(lowerFile)) {
            return FileType.OPENDOCUMENT_TEXT;
        }

        if (logger.isInfoEnabled()) {
            logger.info("getFileType() unknown type=" + lowerFile);
        }

        return FileType.UNKNOWN;
    }
}
