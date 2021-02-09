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

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.Reader;
import java.net.URL;
import java.net.URLConnection;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Iterator;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;

import org.jab.docsearch.DocSearch;
import org.jab.docsearch.DocSearcherIndex;
import org.jab.docsearch.FileEnvironment;
import org.jab.docsearch.utils.DateTimeUtils;
import org.jab.docsearch.utils.FileUtils;
import org.jab.docsearch.utils.Messages;
import org.jab.docsearch.utils.NetUtils;
import org.jab.docsearch.utils.Utils;

/**
 * Class LinkFinder
 * 
 * @version $Id: LinkFinder.java,v 1.9 2005/10/25 19:56:12 henschel Exp $
 */
public final class LinkFinder {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    /**
     * FileEnvironment
     */
    private FileEnvironment fEnv = FileEnvironment.getInstance();
    private int numSkips = 0;
    private DocSearch ds = null;
    private IndexWriter iw;
    private IndexReader ir;
    private int numDeletes = 0;
    private int numChanges = 0;
    private int numNew = 0;
    private int numUnChanged = 0;
    private int numMetaNoIdx = 0;
    private int numFails = 0;
    private long maxFileSizeToGet = 600000;
    private long curModified = 0;
    private long curFiSi = 0;
    private String curContentType = "";
    private String pageName = "";
    private String downloadFile = "dnldfi.tmp";
    private String downloadFileDir = System.getProperty("java.io.tmpdir");
    private DocSearcherIndex dsi;
    private String baseUrlFolder = "";
    private String domainUrl = "";
    private String outFile = "";
    private ArrayList links = new ArrayList();
    private ArrayList skippedLinks = new ArrayList();
    private String[] htmlTypes = {
            ".htm",
            ".shtm",
            ".html",
            ".shtm",
            ".asp",
            ".php",
            ".jsp",
            ".cfm",
            ".cfml",
            ".do",
            ".aspx",
            ".jhtml",
            "/" };
    private String[] nonHtmlTypes = {
            ".zip",
            ".jpg",
            ".bmp",
            ".gif",
            ".db",
            ".cat",
            ".wmf",
            ".tif",
            ".tiff",
            ".swf",
            ".ncd",
            ".pdd",
            ".png",
            ".ppt",
            ".jpeg",
            ".mdb",
            ".msg",
            ".mpp",
            ".log" };
    private String[] bogusDirs = {
            "_vti_",
            "_private",
            "file:" };
    private final static String DOWNLOADING = Messages.getString("DocSearch.dnldg");
    private final static String DOWNLOAD_COMPLETE = Messages.getString("DocSearch.dnldComplete");
    private final static String ERROR = Messages.getString("DocSearch.err");
    private final static String SKIPPING_LINK_TOO_LONG = Messages.getString("DocSearch.lnkTooBig");
    private final static String K_BYTES = Messages.getString("DocSearch.bytes");
    private final static String LINKS_FOUND = Messages.getString("DocSearch.lnxFnd");
    private final static String DOCS_IDXD = Messages.getString("DocSearch.doxIdxd");
    private final static String SKIPPING_LINK = Messages.getString("DocSearch.skippingLink");
    private final static String SUCCESSFUL_DOWNLOADS = Messages.getString("DocSearch.successfulSpiders");
    private final static String FAILED_DOWNLOADS = Messages.getString("DocSearch.failedSpiders");
    private final static String META_DOWNLOADS = Messages.getString("DocSearch.nonMetaSpiders");
    private final static String CONNECTING_TO = Messages.getString("DocSearch.cnktgTo");
    private final static String SPIDERING_COMPLETE = Messages.getString("DocSearch.spideringComplete");
    private int maxLinksToFind = 5000;
  
    /**
     * Main method
     *
     * @param args
     */
    public static void main(String[] args) {
        BasicConfigurator.configure();

        LinkFinder lf = new LinkFinder(args[0], args[1]);
        lf.init();
        lf.getAllLinks();
    }


    /**
     * Constructor
     *
     * @param pageName
     * @param outFile
     */
    public LinkFinder(String pageName, String outFile) {
        this.pageName = pageName;
        this.outFile = outFile;
    }


    /**
     * Constructor
     *
     * @param pageName
     * @param outFile
     * @param maxLinksToFind
     * @param ds
     * @param dsi
     * @param iw
     */
    public LinkFinder(String pageName, String outFile, int maxLinksToFind, DocSearch ds, DocSearcherIndex dsi, IndexWriter iw) {
        this.pageName = pageName;
        this.outFile = outFile;
        this.maxLinksToFind = maxLinksToFind;
        this.ds = ds;
        this.dsi = dsi;
        this.iw = iw;
        downloadFileDir = ds.tempDir;
        maxFileSizeToGet = ds.getMaxFileSize();
    }


    /**
     * Constructor
     *
     * @param pageName
     * @param outFile
     * @param maxLinksToFind
     * @param ds
     * @param dsi
     * @param links
     */
    public LinkFinder(String pageName, String outFile, int maxLinksToFind, DocSearch ds, DocSearcherIndex dsi, ArrayList links) {
        this.pageName = pageName;
        this.outFile = outFile;
        this.maxLinksToFind = maxLinksToFind;
        this.ds = ds;
        this.dsi = dsi;
        this.links = links;
        downloadFileDir = ds.tempDir;
        maxFileSizeToGet = ds.getMaxFileSize();
    }


    /**
     * Method init
     */
    public void init() {
        // Create a trust manager that does not validate certificate chains
        TrustManager[] trustAllCerts = new TrustManager[] {
            new X509TrustManager() {
                public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                    return null;
                }

                public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) {
                    // nothing
                }

                public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) {
                    // nothing
                }
            }
        };

        // Install the all-trusting trust manager
        try {
            SSLContext sc = SSLContext.getInstance("SSL");
            sc.init(null, trustAllCerts, new SecureRandom());
            HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
        }
        catch (Exception e) {
            logger.error("init() failed", e);
        }
    }


    /**
     * Checks page looks like HTML
     * 
     * @param url  url string
     * @return     true is HTML
     */
    private boolean looksLikeHtml(String url) {
        return (url.indexOf("?") != -1);
    }


    /**
     * Checks page is HTML
     * 
     * @param url  url string
     * @return     true is HTML
     */
    private boolean isHtml(String url) {
        String lowerUrl = url.toLowerCase();

        if (looksLikeHtml(url)) {
            return true;
        }

        int numHtmlTypes = htmlTypes.length;
        for (int i = 0; i < numHtmlTypes; i++) {
            if (lowerUrl.endsWith(htmlTypes[i])) {
                return true;
            }
        }

        return false;
    }


    /**
     * Checks page is skip type
     * 
     * @param url  url string
     * @return     true is skip type
     */
    private boolean skipType(String url) {
        String lowerUrl = url.toLowerCase();

        int numNonHtmlTypes = nonHtmlTypes.length;
        for (int i = 0; i < numNonHtmlTypes; i++) {
            if (lowerUrl.endsWith(nonHtmlTypes[i])) {
                return true;
            }
        }

        return false;
    }


    /**
     * Checks for bogus directory
     * 
     * @param url  url string
     * @return     true is bogus directory
     */
    private boolean hasBogusDirs(String url) {
        String lowerUrl = url.toLowerCase();

        int numNonHtmlTypes = bogusDirs.length;
        for (int i = 0; i < numNonHtmlTypes; i++) {
            if (lowerUrl.indexOf(bogusDirs[i]) != -1) {
                return true;
            }
        }

        return false;
    }


    /**
     * Gets the next URL number
     * @return
     */
    private int getNextUrlNo() {
        Iterator it = links.iterator();
        int curPos = 0;
        
        while (it.hasNext()) {
            SpiderUrl spy = (SpiderUrl) it.next();
            
            if (! spy.getIsSpidered()) {
                if (! spy.getIsDeadLink()) {
                    return curPos;
                }
            }
            curPos++;
        }

        return -1;
    }


    /**
     * Gets link name by number
     * 
     * @param linkNumber  link number in list
     * @return            link name
     */
    private String getLinkNameByNo(int linkNumber) {
        SpiderUrl spy = (SpiderUrl) links.get(linkNumber);

        return spy.getUrl();
    }


    /**
     * Gets link URL by number
     *
     * @param linkNumber  link number in list
     * @return            URL
     */
    private SpiderUrl getSpiderUrl(int linkNumber) {
        SpiderUrl spy = (SpiderUrl) links.get(linkNumber);

        return spy;
    }


    /**
     * Get all links from page
     */
    public void getAllLinks() {
        // writes links from a page out to a file
        String urlStr = pageName;
        String shortUrl = "";
        numUnChanged = 0;
        numSkips = 0;
        int numSuccesses = 0;
        int numFailed = 0;
        int numNoRobots = 0;
        addLink(urlStr);
        domainUrl = Utils.getDomainUrl(urlStr);
        if (logger.isDebugEnabled()) {
            logger.debug("getAllLinks() domain url='" + domainUrl + "'");
        }
        SpiderUrl curl = new SpiderUrl(urlStr);
        baseUrlFolder = Utils.getBaseUrlFolder(urlStr);
        int curLinkNo = 0;
        String dnldTmpName = "download.tmp";
        // String curMd5="";
        boolean curIsWebPage = true;
        boolean completedSpider = false;
        boolean isDead = false;
        int curPread = 0;
        if (ds != null) {
            ds.setIsWorking(true);
            ds.setProgressMax(maxLinksToFind);
            ds.setCurProgressMSG("Spidering Files...");
        }
        int numSpidered = 0;
        int curSuccessNo = 0;

        while (curLinkNo != -1) {
            try {
                completedSpider = false;
                isDead = false;
                if (ds != null) {
                    ds.setCurProgress(curPread);
                    if (!ds.getIsWorking())
                        break;
                }
                curLinkNo = getNextUrlNo();
                if (curLinkNo == -1) {
                    logger.debug("getAllLinks() end of links reached.");
                    break;
                }
                else {
                    urlStr = getLinkNameByNo(curLinkNo);
                    logger.info("getAllLinks() analyzing page='" + urlStr + "'");
                    curl = getSpiderUrl(curLinkNo);
                }

                shortUrl = Utils.concatEnd(urlStr, 33);
                setStatus(CONNECTING_TO + " " + shortUrl);

                // open url
                URL url = new URL(urlStr);
                URLConnection conn = url.openConnection();
                conn.setDoInput(true);
                conn.setUseCaches(false);
                conn.setRequestProperty("User-Agent", "DocSearcher " + Messages.getString("DocSearch.version"));
                conn.connect();
                BufferedInputStream urlStream = new BufferedInputStream(conn.getInputStream());

                // get filesize
                int fileSize = conn.getContentLength();
                if (fileSize > maxFileSizeToGet) {
                    String ex = SKIPPING_LINK_TOO_LONG + " (" + fileSize + " > " + maxFileSizeToGet + ") " + shortUrl;
                    setStatus(ex);
                    throw new Exception(ex);
                }

                setStatus(DOWNLOADING + " " + shortUrl + " " + fileSize + " " + K_BYTES);
                curFiSi = fileSize;
                curl.setSize(curFiSi);
                curModified = conn.getLastModified(); // was .getDate();
                curl.setLastModified(curModified);
                curContentType = conn.getContentType();
                if (curContentType != null) {
                    logger.debug("getAllLinks() content type is '" + curContentType + "'");
                }
                else {
                    logger.debug("getAllLinks() Null content type - assuming html anyway.");
                    curContentType = "html";
                }
                curl.setContentType(curContentType);
                // build the value for downloadFile
                dnldTmpName = ds.getDownloadFileName(curl.getContentType(), urlStr.toLowerCase());
                downloadFile = FileUtils.addFolder(downloadFileDir, dnldTmpName);
                curIsWebPage = isHtml(urlStr.toLowerCase()) || (curContentType.toLowerCase().indexOf("html") != -1);
                logger.debug("addAllLinks() saving to " + downloadFile);
                File saveFile = new File(downloadFile);
                FileOutputStream dos = new FileOutputStream(saveFile);
                int curSize = 0;
                int curI = 0;
                int lastPercent = 0;
                StringBuffer tagBuf = new StringBuffer();
                String realTag;
                String lowerTag;
                String link = null;
                boolean inTag = false;
                boolean getFileSizeFromStream = false;
                if (fileSize == -1) {
                    getFileSizeFromStream = true;
                }
                
                while ((curI = urlStream.read())!= -1) {
                    dos.write(curI);

                    curSize++;
                    if (ds != null) {
                        if (! ds.getIsWorking()) {
                            break;
                        }
                    }

                    // fix problem if filesize not in content length
                    if (getFileSizeFromStream) {
                        fileSize = curSize + urlStream.available();                        
                    }
                    
                    // notify of download progress
                    if (curSize > 0 && (curSize % 10) == 0) {
                        int curPercent = (curSize * 100) / fileSize;
                        if (curPercent != lastPercent) {
                            lastPercent = curPercent;
                            setStatus(DOWNLOADING + " : (" + shortUrl + ") --> " + curPercent + " %" + " ( " + (numSuccesses + numFailed + numNoRobots) + "/" + getNumLinksFound() + ")");
                        }
                    } // end for percent updates
                    else if (curSize % 40 == 0) {
                        setStatus(DOWNLOADING + " : (" + shortUrl + ") --> " + curSize + " " + K_BYTES);
                    }
                    // handle links
                    if (curIsWebPage) {
                        char c = (char) curI;
                        // LOOK AT THE TAGS

                        // start tags
                        if (c == '<') {
                            inTag = true;
                            tagBuf = new StringBuffer();
                        }
                        // end tags
                        else if (c == '>') {
                            tagBuf.append(c);
                            realTag = tagBuf.toString();
                            lowerTag = realTag.toLowerCase();
                            if (lowerTag.startsWith("</a")) {
                                doPossibleAdd(urlStr, link);
                            }
                            else if (lowerTag.startsWith("<area")) {
                                link = Utils.getTagString("href=", realTag);
                                link = Utils.getNormalUrl(link);

                                doPossibleAdd(urlStr, link);
                            }
                            else if (lowerTag.startsWith("<param")) {
                                String appletParam = Utils.getTagString("name=", realTag);
                                if (appletParam.toLowerCase().equals("url")) {
                                    link = Utils.getTagString("value=", realTag);
                                    link = Utils.getNormalUrl(link);

                                    doPossibleAdd(urlStr, link);
                                    doPossibleAdd(urlStr, link);
                                }
                            }
                            //else if (lowerTag.startsWith("<a href=")) {
                            else if (lowerTag.startsWith("<a ")) {
                                link = Utils.getTagString("href=", realTag);
                                link = Utils.getNormalUrl(link);
                            }
                            inTag = false;
                        }

                        // in tag
                        if (inTag) {
                            tagBuf.append(c);
                        }
                    }

                    // past our limit yet?
                    if (numSpidered > maxLinksToFind) {
                        break;
                    }
                } // end while downloading
                curPread++;
                if (numSpidered > maxLinksToFind) {
                    break;
                }
                dos.close();
                urlStream.close();
                curl.setMd5(FileUtils.getMD5Sum(downloadFile));

                // now add out document
                if (ds != null) {
                    curSuccessNo = ds.idx.addDocToIndex(downloadFile, iw, dsi, false, curl);
                    switch (curSuccessNo) {
                        case 0: // good
                            numSuccesses++;
                            break;
                        case 1: // bad
                            numFailed++;
                            break;
                        case 2: // meta robots - no index
                            numNoRobots++;
                            break;
                    }
                }
                
                numSpidered++;
                completedSpider = true;
            }
            catch (Exception e) {
                logger.fatal("addAllLinks() failed", e);
                setStatus(ERROR + " : " + e.toString());
                isDead = true;
            }
            finally {
                curl.setSpidered(completedSpider);
                curl.setIsDeadLink(isDead);
                setStatus(DOWNLOAD_COMPLETE + " " + shortUrl);
            }
        } // end for iterating over links

        ds.resetProgress();
        saveAllLinks();

        logger.info("getAllLinks() " + numSpidered + " total web pages spidered for links.");

        showMessage(SPIDERING_COMPLETE + " (" + Utils.concatStrToEnd(pageName, 28) + ") ", numSpidered + " " + DOCS_IDXD + " " + getNumLinksFound() + " " + LINKS_FOUND + "\n\n" + numSuccesses + " " + SUCCESSFUL_DOWNLOADS + "\n\n" + numFailed + " " + FAILED_DOWNLOADS + "\n\n" + numNoRobots + " " + META_DOWNLOADS);
    }


    /**
     * Has base url
     *
     * @param toCheck
     * @return
     */
    private boolean hasBaseUrl(String toCheck) {
        boolean retB = false;
        if (baseUrlFolder.equals("")) {
            retB = true;
            logger.info("hasBaseUrl() no base url!");
        } else {
            String lowerCheck = toCheck.toLowerCase();
            String lowerBase = baseUrlFolder.toLowerCase();
            if (lowerCheck.startsWith(lowerBase))
                retB = true;
        }
        return retB;
    }


    /**
     * Sets status
     *
     * @param toSet
     */
    private void setStatus(String toSet) {
        if (ds != null) {
            ds.setStatus(toSet);
        }
    }


    /**
     * Method doPossibleAdd
     *
     * @param page
     * @param link
     */
    public void doPossibleAdd(String page, String link) {
        if (logger.isDebugEnabled()) {
            logger.debug("doPossibleAdd('" + page + "', '" + link + "') entered");
        }

        link = link.trim();
        
        if (! link.equals("")  && link.indexOf("mailto:") == -1) {
            if (link.indexOf("#") != -1) {
                int anchorPos = link.indexOf("#");
                link = link.substring(0, anchorPos);
            }
            if (link.indexOf("\\") != -1) {
                link = Utils.replaceAll("\\", link, "/");
            }
            if (link.startsWith("'") && link.endsWith("'")) {
                link = link.substring(1, link.length() - 1);
            }

            // DETERMINE LINK SIZE
            long size = 0;
            LinkValue lv = new LinkValue(page, link);
            String realUrl = lv.getRealLink();
            // System.out.println("Examining url: "+realUrl);

            //
            if (realUrl.toLowerCase().startsWith(domainUrl.toLowerCase()) && ! hasBogusDirs(realUrl) && hasBaseUrl(realUrl) && ! skipType(realUrl)) {
                if (! realUrl.equals("")) {
                    size = NetUtils.getURLSize(realUrl);
                }
                // System.out.println("Size is "+size);
                if (size != 0) {
                    /* add the link becuase it has size */
                    // System.out.println("Adding link:"+realUrl);
                    addLink(realUrl);
                }
                else {
                    /* skip the link because size is -1 (broken?) */
                    setStatus(SKIPPING_LINK + " : " + realUrl + "\nSIZE=" + size);
                    skippedLinks.add(realUrl);
                    numSkips++;
                }
            } // end for url has domain prefix
            else {
                if (logger.isDebugEnabled()) {
                    logger.debug("doPossibleAdd() real url='" + realUrl + "' skipped because it doesn't start with '" + domainUrl + "', or url is not an indexible file type.");
                }
            }
            link = "";
        }
        else {
            if (logger.isDebugEnabled()) {
                logger.debug("doPossibleAdd() link='" + link + "' was a mailto or empty.");
            }
        }
    }


    /**
     * Adds link to list
     *
     * @param newUrl
     */
    private void addLink(String newUrl) {
        if (logger.isDebugEnabled()) {
            logger.debug("addLink() adding link to list='" + newUrl + "'");
        }

        int newLen = newUrl.length();
        Iterator it = links.iterator();
        int curPos = 0;
        boolean okToAdd = true;

        if (! links.isEmpty()) {
            while (it.hasNext()) {
                SpiderUrl turl = (SpiderUrl) it.next();
                String curUrlString = turl.getUrl();
                int curLen = curUrlString.length();

                if (newLen == curLen) {
                    if (newUrl.equals(curUrlString)) {
                        okToAdd = false;
                    }
                    else if (newUrl.equalsIgnoreCase(curUrlString)) {
                        okToAdd = false;
                    }
                }
                else if (newLen > curLen) {
                    // curPos++;
                    break;
                }
                curPos++;
            }
        }

        if (okToAdd) {
            SpiderUrl surl = new SpiderUrl(Utils.replaceAll("|", newUrl, "%7C"));
            links.add(curPos, surl);
        } else {
            if (logger.isDebugEnabled()) {
                logger.debug("addLink() discarding link='" + newUrl + "'");
            }
        }
    }


    /**
     * getNumLinksFound
     *
     * @return
     */
    private int getNumLinksFound() {
        return links.size();
    }


    /**
     * Saves all links
     */
    private void saveAllLinks() {

        // now save the output to a file
        String outBad = FileUtils.addFolder(fEnv.getIndexDirectory(), Utils.replaceAll(" ", dsi.getDescription(), "_") + "_bad_links.txt");
        if (ds != null) {
            outFile = FileUtils.addFolder(fEnv.getIndexDirectory(), Utils.replaceAll(" ", dsi.getDescription(), "_") + ".txt");
        }
        File saveFi = new File(outFile);
        File saveBadF = new File(outBad);

        PrintWriter pw = null;
        PrintWriter bpw = null;
        try {
            pw = new PrintWriter(new FileWriter(saveFi));
            bpw = new PrintWriter(new FileWriter(saveBadF));
            
            Iterator it = links.iterator();
            while (it.hasNext()) {
                SpiderUrl spy = (SpiderUrl) it.next();
                if (! spy.getIsDeadLink()) {
                    pw.println(spy.getUrl() + "|" + spy.getLastModified() + "|" + spy.getSize() + "|" + spy.getContentType() + "|" + spy.getMd5());
                }
                else {
                    bpw.println(spy.getUrl());
                }
            }
            setStatus(links.size() + " total links found, " + numSkips + " links skipped.");
            
            if (skippedLinks.size() > 0) {
                Iterator sit = skippedLinks.iterator();
                while (sit.hasNext()) {
                    logger.debug("saveAllLinks() skippedLink='" +  sit.next() + "'");
                }
            }
        }
        catch (IOException ioe) {
            logger.fatal("saveAllLinks() failed", ioe);
        }
        finally {
            if (pw != null) {
                pw.close();
            }
            if (bpw != null) {
                bpw.close();
            }
        }
    }


    /**
     * Shows message
     *
     * @param title
     * @param details
     */
    private void showMessage(String title, String details) {
        if (ds != null) {
            ds.showMessage(title, details);
        }
        else {
            logger.info("showMessage() " + title + "\n" + details);
        }
    }


    /**
     * Checks file for links
     *
     * @param origFile
     * @param thisPageName
     */
    private void checkFileForLinks(String origFile, String thisPageName) {
        String urlStr = thisPageName;
        String shortUrl = Utils.concatEnd(thisPageName, 33);
        if (ds != null) {
            setStatus(DocSearch.dsLkngFoLnx + " " + shortUrl);
        }
        domainUrl = Utils.getDomainUrl(urlStr);
        String realTag;
        String lowerTag;
        boolean inTag = false;
        String link = null;
        long lastPcnt = 0;
        File testFi = new File(origFile);
        long thisFileSize = testFi.length();
        long curDnldnd = 0;
        StringBuffer tagBuf = new StringBuffer();
        baseUrlFolder = Utils.getBaseUrlFolder(urlStr);
        try {
            FileInputStream fi = new FileInputStream(origFile);
            Reader in = new BufferedReader(new InputStreamReader(fi));
            // close the readers, etc...
            int ch;
            while ((ch = in.read()) > -1) {
                char c = (char) ch;
                curDnldnd++;
                
                if (thisFileSize > 0) {
                    if (curDnldnd % 10 == 0) {
                        long curPcnt = (curDnldnd * 100) / thisFileSize;
                        if (curPcnt != lastPcnt) {
                            lastPcnt = curPcnt;
                            setStatus(DocSearch.dsLkngFoLnx + " " + shortUrl + " --> (" + curPcnt + " %)");
                        }
                    }
                }
                
                // start tags
                if (c == '<') {
                    inTag = true;
                    tagBuf = new StringBuffer();
                }
                // end tags
                else if (c == '>') {
                    tagBuf.append(c);
                    realTag = tagBuf.toString();
                    lowerTag = realTag.toLowerCase();
                    
                    if (lowerTag.startsWith("</a")) {
                        doPossibleAdd(thisPageName, link);
                    }
                    else if (lowerTag.startsWith("<area")) {
                        link = Utils.getTagString("href=", realTag);
                        link = Utils.getNormalUrl(link);

                        doPossibleAdd(thisPageName, link);
                    }
                    else if (lowerTag.startsWith("<param")) {
                        String appletParam = Utils.getTagString("name=", realTag);
                        if (appletParam.toLowerCase().equals("url")) {
                            link = Utils.getTagString("value=", realTag);
                            link = Utils.getNormalUrl(link);

                            doPossibleAdd(thisPageName, link);
                        }
                    }
                    //else if (lowerTag.startsWith("<a href=")) {
                    else if (lowerTag.startsWith("<a ")) {
                        link = Utils.getTagString("href=", realTag);
                        link = Utils.getNormalUrl(link);
                    }
                    inTag = false;
                }
                //
                if (inTag) {
                    tagBuf.append(c);
                }
            }

            in.close();
            fi.close();
        } catch (IOException ioe) {
            logger.fatal("checkFileForLinks() failed", ioe);
        }
    }


    /**
     * Gets number of deletes
     *
     * @return
     */
    public int getNumDeletes() {
        return numDeletes;
    }


    /**
     * Gets number of updates
     *
     * @return
     */
    public int getNumUpdates() {
        return numChanges;
    }


    /**
     * Gets number of news
     * @return
     */
    public int getNumNew() {
        return numNew;
    }


    /**
     * Gets number of fails
     *
     * @return
     */
    public int getNumFails() {
        return numFails;
    }


    /**
     * Gets number of unchanges
     * @return
     */
    public int getNumUnchanged() {
        return numUnChanged;
    }


    /**
     * Gets number of meta no index
     *
     * @return
     */
    public int getNumMetaNoIdx() {
        return numMetaNoIdx;
    }


    /**
     * Method update
     *
     * @throws IOException
     */
    public void update() throws IOException {
        numDeletes = 0;
        numChanges = 0;
        numNew = 0;
        numFails = 0;
        numUnChanged = 0;
        numMetaNoIdx = 0;

        ir = IndexReader.open(dsi.getIndexPath());
        int maxNumDocs = ir.maxDoc();
        int maxTotal = maxNumDocs + maxNumDocs / 10;
        ds.setStatus(DocSearch.dsTtlDxInIdx + " " + maxNumDocs);
        int curDocNum = 0;
        if (ds != null) {
            ds.setIsWorking(true);
            ds.setProgressMax(maxTotal * 2);
            ds.setCurProgressMSG("Spidering Files...");
        }

        // assign index location to urls currently in the index
        Iterator it = links.iterator();
        int lastFound = 0;
        while (it.hasNext()) {
            curDocNum++;

            if (ds != null) {
                ds.setCurProgress(curDocNum);
                if (! ds.getIsWorking()) {
                    break;
                }
            }

            SpiderUrl spy = (SpiderUrl) it.next();
            String curFi = spy.getUrl();
            lastFound = ds.idx.spiderIndexNum(lastFound, curFi, ir);
            spy.setIndexLocation(lastFound);
            
            if (lastFound == -1) {
                logger.debug("update() " + curFi + " currently is not in the index");
            }
        }

        // now iterate over all the spider urls
        int curSpiderNum = getNextUrlNo();
        int totalSpidered = 0;
        while (curSpiderNum != -1) {
            curDocNum++;

            if (ds != null) {
                ds.setCurProgress(curDocNum);
                if (! ds.getIsWorking()) {
                    break;
                }
            }

            SpiderUrl curSpider = getSpiderUrl(curSpiderNum);
            String curFi = curSpider.getUrl();
            int curNumLinksFound = getNumLinksFound();
            int curIdxNum = curSpider.getIndexLocation();
            // TODO size and date in one reqest!! this is faster
            long curUrlSize = NetUtils.getURLSize(curSpider.getUrl());
            long curModified = NetUtils.getURLModifiedDate(curSpider.getUrl());
            String shortUrl = Utils.concatEnd(curFi, 33);
            String dnldTmpName = ds.getDownloadFileName(curSpider.getContentType(), curFi.toLowerCase());
            String downloadFile = FileUtils.addFolder(downloadFileDir, dnldTmpName);
            if (curUrlSize > maxFileSizeToGet) {
                String ex = SKIPPING_LINK_TOO_LONG + " (" + curUrlSize + " > " + maxFileSizeToGet + ") " + shortUrl;
                setStatus(ex);
            }
            else if (curIdxNum != -1) {
                if (logger.isDebugEnabled()) {
                    logger.debug("update() '" + shortUrl + "' is in index");
                }
                ds.setStatus(DocSearch.dsCkgFoUpdtsToDoc + " " + shortUrl + " (" + totalSpidered + " / " + curNumLinksFound + ")");
                int curSpiderStatus = NetUtils.getURLStatus(curSpider, downloadFile);
                switch (curSpiderStatus) {
                    case -1: // broken url
                        curSpider.setIsDeadLink(true);
                        ds.setStatus(DocSearch.dsBknLink + " " + shortUrl);
                        // remove from index
                        ir.delete(curIdxNum);
                        numDeletes++;
                        break;
                    case 0: // same
                        ds.setStatus(DocSearch.lnkNoChanges + " " + shortUrl);
                        numUnChanged++;
                        totalSpidered++;
                        break;
                    case 1: // changed
                        ds.setStatus(DocSearch.dsReIdxgLnk + " " + shortUrl);
                        ir.delete(curIdxNum);
                        ir.close();
                        String curHash = FileUtils.getMD5Sum(downloadFile);
                        curUrlSize = FileUtils.getFileSize(downloadFile);
                        curSpider.setMd5(curHash);
                        curSpider.setLastModified(curModified);
                        curSpider.setSize(curUrlSize);
                        iw = new IndexWriter(dsi.getIndexPath(), new StandardAnalyzer(), false);
                        // iw.setUseCompoundFile(true);
                        int curAddedSuccess = ds.idx.addDocToIndex(downloadFile, iw, dsi, false, curSpider);
                        iw.close();
                        ir = IndexReader.open(dsi.getIndexPath());
                        if (curAddedSuccess == 0) {
                            numChanges++;
                            totalSpidered++;
                        }
                        else if (curAddedSuccess == 2) {
                            numMetaNoIdx++;
                        }
                        else if (curAddedSuccess == 1) {
                            logger.warn("update() indexing failed " + shortUrl);
                            numFails++;
                        }

                        // get links from downloaded file
                        if (isHtml(curSpider.getUrl().toLowerCase())) {
                            checkFileForLinks(downloadFile, curSpider.getUrl());
                        }
                        break;
                }
            } // end for its already in the index
            else {
                if (logger.isDebugEnabled()) {
                    logger.debug("update() '" + shortUrl + "' is in index");
                }
                // get links from downloaded file
                ds.setStatus(DocSearch.dsSpiderNewUrl + " " + shortUrl + " (" + totalSpidered + " / " + curNumLinksFound + ")");
                boolean downloadOk = NetUtils.downloadURLToFile(curSpider.getUrl(), downloadFile);
                if (downloadOk) {
                    String curHash = FileUtils.getMD5Sum(downloadFile);
                    curSpider.setMd5(curHash);
                    curSpider.setLastModified(curModified);
                    curSpider.setSize(curUrlSize);
                    iw = new IndexWriter(dsi.getIndexPath(), new StandardAnalyzer(), false);
                    // iw.setUseCompoundFile(true);
                    int curAddedSuccess = ds.idx.addDocToIndex(downloadFile, iw, dsi, false, curSpider);
                    iw.close();
                    ir.close();
                    ir = IndexReader.open(dsi.getIndexPath());
                    if (curAddedSuccess == 0) {
                        numNew++;
                        totalSpidered++;
                    }
                    else if (curAddedSuccess == 2) {
                        numMetaNoIdx++;
                    }
                    else if (curAddedSuccess == 1) {
                        logger.warn("update() indexing failed " + shortUrl);
                        numFails++;
                    }
                    if (isHtml(curSpider.getUrl())) {
                        checkFileForLinks(downloadFile, curSpider.getUrl());
                    }
                }
                else {
                    setStatus(DocSearch.dsBknLink + " " + shortUrl);
                    curSpider.setIsDeadLink(true);
                } // end for unable to download
            } // its not in the index

            // last things to do
            curSpider.setSpidered(true);
            curSpider.setLastModified(curModified);
            curSpider.setSize(curUrlSize);
            curSpiderNum = getNextUrlNo();
            if (curSpiderNum == -1) {
                break;
            }
            if (totalSpidered > maxTotal) {
                break;
            }
        } // end while iterating over the links

        ds.setStatus(DocSearch.dsSpdrUpdteComp + " " + dsi.getDescription());
        saveAllLinks();
        if (! skippedLinks.isEmpty()) {
            Iterator sit = skippedLinks.iterator();
            while (sit.hasNext()) {
                logger.warn("update() skipped link='" + sit.next() + "'");
            }
        }

        // update the date of the index
        dsi.setLastIndexed(DateTimeUtils.getToday());
        ir.close();
        ds.resetProgress();
    }
}
