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

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import org.apache.log4j.Logger;
import org.apache.lucene.document.DateField;

/**
 * This class contains useful method for handling dates
 * 
 * @version $Id: DateTimeUtils.java,v 1.7 2005/10/11 21:04:38 henschel Exp $
 */
public class DateTimeUtils {
    /**
     * Log4J
     */
    private final static Logger logger = Logger.getLogger(DateTimeUtils.class.getName());

    /**
     * Gets file date
     *
     * @param modDate
     * @return
     */
    public static String getFileDate(String modDate) {
        StringBuffer retB = new StringBuffer();

        Calendar nowD = Calendar.getInstance();
        Date dn = getJDateFromString(modDate);
        nowD.setTime(dn);

        int mon = nowD.get(Calendar.MONTH) + 1;
        int year = nowD.get(Calendar.YEAR);
        int day = nowD.get(Calendar.DAY_OF_MONTH);

        retB.append(year + "");

        if (mon < 10) {
            retB.append("0");
        }
        retB.append(mon + "");

        if (day < 10) {
            retB.append("0");
        }
        retB.append(day + "");

        return retB.toString();
    }


    /**
     * Gets JDate from string
     *
     * @param dateStr
     * @return
     */
    public static Date getJDateFromString(String dateStr) {
        // DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT);
        // (12.13.52 or 3:30pm ????)
        // SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd"); (better,
        // but more changes in code)
        SimpleDateFormat df = new SimpleDateFormat("M/d/yyyy");

        Date rd = null;
        try {
            rd = df.parse(dateStr);
        }
        catch (Exception eR) {
            logger.error("getJDateFromString() failed during parsing date=" + dateStr);
        }

        // Date rd = new Date(dateStr);
        // System.out.println("date:"+rd.toString());
        return rd;
    }


    /**
     * Gets days old
     *
     * @param date
     * @return
     */
    public static int getDaysOld(String date) {
        int returnInt = 0;

        if (! date.equals("")) {
            long indexTime;
            long nowTime;
            Date today = getJDateFromString(getToday());
            Date then = getJDateFromString(date);
            nowTime = today.getTime();
            indexTime = then.getTime();

            // perform math to compute the actual number of days
            if (nowTime > indexTime) {
                indexTime = indexTime / (1000 * 60 * 60 * 24);
                nowTime = nowTime / (1000 * 60 * 60 * 24);
                returnInt = (int) (nowTime - indexTime);
            }
        }

        return returnInt;
    }


    /**
     * Gets today
     *
     * @return
     */
    public static String getToday() {
        Calendar nowD = Calendar.getInstance();
        String mon = "" + (nowD.get(Calendar.MONTH) + 1);
        String year = "" + (nowD.get(Calendar.YEAR));
        String day = "" + nowD.get(Calendar.DAY_OF_MONTH);
        
        return mon + "/" + day + "/" + year;
    }


    /**
     * Gets last year
     *
     * @return
     */
    public static String getLastYear() {
        // String lastYear = "";
        Calendar nowD = Calendar.getInstance();
        String mon = "" + (nowD.get(Calendar.MONTH) + 1);
        String year = "" + (nowD.get(Calendar.YEAR));
        String day = "" + nowD.get(Calendar.DAY_OF_MONTH);
        // String reportDate = mon + "/" + day + "/" + year;
        int ly = 2002;
        try {
            ly = Integer.parseInt(year) - 1;
        }
        catch (NumberFormatException nfe) {
            logger.warn("getLastYear()");
            ly = 2002;
        }

        // return lastYear = mon + "/" + day + "/" + ly;
        return mon + "/" + day + "/" + ly;
    }


    /**
     * Gets file date
     *
     * @param modDate
     * @return
     */
    public static String getFileDate(long modDate) {
        StringBuffer retB = new StringBuffer();

        Calendar nowD = Calendar.getInstance();
        Date dn = new Date(modDate);
        nowD.setTime(dn);

        int mon = nowD.get(Calendar.MONTH) + 1;
        int year = nowD.get(Calendar.YEAR);
        int day = nowD.get(Calendar.DAY_OF_MONTH);

        retB.append(year + "");

        if (mon < 10) {
            retB.append("0");
        }
        retB.append(mon + "");

        if (day < 10) {
            retB.append("0");
        }
        retB.append(day + "");

        return retB.toString();
    }


    /**
     * Gets normal file date
     *
     * @param modDate
     * @return
     */
    public static String getNormalFileDate(long modDate) {
        StringBuffer retB = new StringBuffer();

        Calendar nowD = Calendar.getInstance();
        Date dn = new Date(modDate);
        nowD.setTime(dn);

        int mon = nowD.get(Calendar.MONTH) + 1;
        int year = nowD.get(Calendar.YEAR);
        int day = nowD.get(Calendar.DAY_OF_MONTH);

        retB.append(mon + "/");
        retB.append(day + "/");
        retB.append(year + "");

        return retB.toString();
    }


    /**
     * Gets data format normal
     * @param toConv
     * @return
     */
    public static String getDateFormatNormal(String toConv) {
        return getDateParsed(toConv);
    }


    /**
     * unused and false DateFormat
     * 
     * @param s
     * @return
     *
    private static String getDateFromField(String s) {
        String returnString = "";
        try {
            DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT);
            returnString = DateField.dateToString(df.parse(s));

            logger.debug("getDateFromField() Converted date:" + s + " TO " + returnString);
            return returnString;
        }
        catch (Exception eR) {
            logger.error("getDateFromField() Unable to convert date from field info:" + s);
            return "Unknown";
        }
    }*/


    /**
     * Returns time string for index
     *
     * @param ltime
     * @return       time string
     */
    public static String getTimeStringForIndex(long ltime) {
        return DateField.timeToString(ltime);
    }


    /**
     * Gets data parsed
     *
     * @param s
     * @return
     */
    public static String getDateParsed(String s) {
        Date bd = DateField.stringToDate(s);
        Calendar nowD = Calendar.getInstance();
        nowD.setTime(bd);

        int mon = nowD.get(Calendar.MONTH) + 1;
        int year = nowD.get(Calendar.YEAR);
        int day = nowD.get(Calendar.DAY_OF_MONTH);

        return mon + "/" + day + "/" + year;
    }


    /**
     * Gets data index
     *
     * @param timeOfFile
     * @return
     */
    public static String getDateIndex(long timeOfFile) {
        String returnString = getNormalFileDate(timeOfFile);

        returnString = getDateParsed(returnString);

        return returnString;
    }
}
