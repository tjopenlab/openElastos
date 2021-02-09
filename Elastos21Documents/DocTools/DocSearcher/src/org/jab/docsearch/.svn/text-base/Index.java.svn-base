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
package org.jab.docsearch;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.Reader;
import java.util.ArrayList;

import org.apache.log4j.Logger;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;

import org.jab.docsearch.constants.FileType;
import org.jab.docsearch.converters.Excel;
import org.jab.docsearch.converters.OoToText;
import org.jab.docsearch.converters.OpenDocument;
import org.jab.docsearch.converters.PdfToText;
import org.jab.docsearch.converters.RtfToText;
import org.jab.docsearch.converters.Word;
import org.jab.docsearch.spider.LinkFinder;
import org.jab.docsearch.spider.SpiderUrl;
import org.jab.docsearch.utils.DateTimeUtils;
import org.jab.docsearch.utils.FileTypeUtils;
import org.jab.docsearch.utils.FileUtils;
import org.jab.docsearch.utils.Messages;
import org.jab.docsearch.utils.Utils;
import org.jab.docsearch.utils.WebPageMetaData;

/**
 * Performs manipulations of a DocSearcherIndex.
 * 
 * @see DocSearcherIndex DocSearcherIndex
 * @version $Id: Index.java,v 1.22 2006/08/16 19:48:46 henschel Exp $
 */
public class Index {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    /**
     * FileEnvironment
     */
    private FileEnvironment fEnv = FileEnvironment.getInstance();
    private DocSearch ds;
    private final static String META_TAG = "<meta";
    private final static String BODY_TAG = "<body";
    private final static String BODY_TAG_END = "</body";
    private final static String TITLE_TAG = "<title";
    private final static String TITLE_TAG_END = "</title";
    private final static String SCRIPT_TAG = "<script";
    private final static String SCRIPT_TAG_END = "</script";
    private StringBuffer notesBuf = new StringBuffer();
    private StringBuffer newItsBuf = new StringBuffer();
    private StringBuffer modItsItsBuf = new StringBuffer();
    private StringBuffer delItsItsBuf = new StringBuffer();
    private int totalChanges = 0;
    private boolean isTextEmailFormat = true;
    private boolean doEmail = false;
    private int insertMode = 0; // 0 = new, 1 = modified, 2 = deleted
    private final static String pathSep = FileUtils.PATH_SEPARATOR;


    /**
     * Constructor
     *
     * @param ds
     */
    public Index(DocSearch ds) {
        this.ds = ds;
    }


    /**
     * Attempts to index a document and returns a result code that indicates
     * success or failure
     * 
     * @return 0 if indexing went OK, 1 if an error occurred that prevented
     *         indexing, 2 if the meta data indicates that the document should
     *         not be indexed
     */
    public int addDocToIndex(String currentFi, IndexWriter writer, DocSearcherIndex di, boolean isCdRomIndx, SpiderUrl spy) {
        if (logger.isInfoEnabled()) {
            logger.info("addDocToIndex() adding " + currentFi + " to index");
        }
        
        boolean isSpiderFile = di.getIsSpider();
        // 0 = OK, 1 = failed, 2 = meta robots = noindex....
        int returnInt = 0;
        // boolean thisErr = false;

        synchronized (this) {
            try {
                Document doc = new Document();
                String urlStr = "";
                String author = null;
                String keyWords = null;
                String curTitle = null;
                String dateStr;
                String curSummary = null;
                String documentText = null;
                File curFile = new File(currentFi);
                long curFileSize = curFile.length();
                InputStream is; // for our file
                String curType = FileUtils.getFileExtension(currentFi);
                String lowerType = curType.toLowerCase();
                int typeInt = FileTypeUtils.getFileType(lowerType);

                // file
                if (isSpiderFile) {
                    if (spy.getContentType().toLowerCase().indexOf("html") != -1) {
                        typeInt = FileType.HTML;
                    }

                    dateStr = DateTimeUtils.getTimeStringForIndex(spy.getLastModified());
                    urlStr = spy.getUrl();
                }
                // web/cdrom
                else {
                    dateStr = DateTimeUtils.getTimeStringForIndex(curFile.lastModified());

                    // web
                    if (di.getIsWeb()) {
                        urlStr = Utils.getURL(currentFi, di.getReplace(), di.getMatch());
                    }
                    // cdrom
                    else if (isCdRomIndx) {
                        urlStr = Utils.getURL(currentFi, di.getReplace(), di.getMatch());
                    }
                }

                // use the correct data extractor
                switch (typeInt) {
                    case FileType.HTML: { // html
                        WebPageMetaData wpmd = getWebPageMetaData(currentFi);

                        curTitle = wpmd.getTitle();
                        curSummary = wpmd.getDescription();
                        author = wpmd.getAuthor();
                        is = new FileInputStream(ds.htmlTextFile);
                        break;
                    }
                    case FileType.TEXT: { // text 
                        curTitle = getDocTitle(currentFi, typeInt);
                        curSummary = getDocSummary(currentFi, typeInt);
                        is = new FileInputStream(currentFi);
                        break;
                    }
                    case FileType.MS_WORD: { // ms word
                        Word word = new Word(currentFi);
                        word.parse();

                        author = word.getAuthor();
                        keyWords = word.getKeywords();
                        curTitle = word.getTitle();
                        curSummary = word.getSummary();
                        documentText = word.getText();
                        is = null;
                        break;
                    }
                    case FileType.MS_EXCEL: { // ms excel
                        Excel excel = new Excel(currentFi);
                        excel.parse();

                        author = excel.getAuthor();
                        keyWords = excel.getKeywords();
                        curTitle = excel.getTitle();
                        curSummary = excel.getSummary();
                        documentText = excel.getText();
                        is = null;
                        break;
                    }
                    case FileType.PDF: { // pdf
                        PdfToText pp = new PdfToText(currentFi, ds.pdfTextFile);

                        // try multivalent first - if that fails - then try PDF Box
                        if (pp.doMultiValent()) {
                            curSummary = getDocSummary(ds.pdfTextFile, typeInt);
                            is = new FileInputStream(ds.pdfTextFile);
                        }
                        else {
                            logger.warn("addDocToIndex() Multivalent parsing failed - now try PDFBox");

                            if (pp.didParse()) {
                                curSummary = pp.getSummary();
                                if (curSummary == null || curSummary.equals("")) {
                                    curSummary = getDocSummary(ds.pdfTextFile, typeInt);
                                }
                                author = pp.getAuthor();
                                keyWords = pp.getKeywords();
                                curTitle = pp.getTitle();
                                is = new FileInputStream(ds.pdfTextFile);
                            }
                            else {
                                logger.error("addDocToIndex() error parsing PDF socument:\n" + pp.getErrText() + "\n - skipping " + currentFi);
                                throw new Exception("PDF Parsing Error:Unable to parse document --> " + currentFi);
                            }
                        }

                        break;
                    }
                    case FileType.RTF:  { // rtf
                        RtfToText rp = new RtfToText(currentFi, ds.rtfTextFile);
                        rp.parse();

                        curSummary = getDocSummary(ds.rtfTextFile, typeInt);
                        is = new FileInputStream(ds.rtfTextFile);
                        break;
                    }
                    case FileType.OO_WRITER: // openoffice writer
                    case FileType.OO_IMPRESS:  // openoffice impress
                    case FileType.OO_CALC:  // openoffice calc
                    case FileType.OO_DRAW: { // openoffice draw
                        OoToText op = new OoToText(currentFi, ds.ooTextFile, ds.ooMetaTextFile);
                        op.parse();

                        author = getTagText("creator", ds.ooMetaTextFile);
                        keyWords = Utils.nonTagText(getTagText("keywords", ds.ooMetaTextFile));
                        removeAllTags(ds.ooTextFile, ds.ooTextOnlyFile);
                        curSummary = getDocSummary(ds.ooTextOnlyFile, typeInt);
                        curTitle = getTagText("title", ds.ooMetaTextFile);
                        is = new FileInputStream(ds.ooTextOnlyFile);
                        break;
                    }
                    case FileType.OPENDOCUMENT_TEXT: { // opendocument text
                        OpenDocument od = new OpenDocument(currentFi);
                        od.parse();

                        author = od.getAuthor();
                        keyWords = od.getKeywords();
                        curTitle = od.getTitle();
                        curSummary = od.getSummary();
                        documentText = od.getText();
                        is = null;
                        break;
                    }
                    default: { // text
                        curTitle = getDocTitle(currentFi, typeInt);
                        curSummary = getDocSummary(currentFi, typeInt);
                        is = new FileInputStream(currentFi);
                        break;
                    }
                }

                // spider url stuff
                if (isSpiderFile) {
                    if (curTitle == null || curTitle.trim().equals("")) {
                        curTitle = Utils.getNameOnly(urlStr);
                    }
                }

                // repair missing meta data - if needed
                if (curTitle == null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("addDocToIndex() title of '" + currentFi + "' is null!");
                    }
                    curTitle = "";
                }
                if (curTitle.trim().equals("")) {
                    curTitle = Utils.getNameOnly(currentFi);
                }
                if (author == null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("addDocToIndex() author of '" + currentFi + "' is null!");
                    }
                    author = "";
                }
                if (keyWords == null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("addDocToIndex() keywords of '" + currentFi + "' are null!");
                    }
                    keyWords = "";
                }
                if (curSummary == null) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("addDocToIndex() summary of '" + currentFi + "' is null!");
                    }
                    curSummary = "";
                }
                if ((typeInt == FileType.TEXT) && (curSummary.toLowerCase().indexOf("noindex") != -1)) {
                    // if its a text document with NOINDEX in the start of the
                    // text - don't index it
                    ds.setStatus("Document " + currentFi + " PREFERS no indexing.");
                    returnInt = 2;
                }
                else if (typeInt == FileType.HTML) {
                    // web page - check for meta name = robots content =
                    // noindex...
                    String metaRobot = getMetaTag(currentFi, "robots");
                    if (metaRobot.toLowerCase().indexOf("noindex") != -1) {
                        // thisErr = true;
                        ds.setStatus("Document " + currentFi + " PREFERS no indexing.");
                        returnInt = 2;
                    }
                }

                // lastly add our document
                if (returnInt == 0) {
                    if (isSpiderFile) {
                        doc.add(Field.UnIndexed("md5", spy.getMd5()));
                    }
                    doc.add(Field.UnIndexed("path", currentFi));
                    doc.add(Field.Keyword("size", Long.toString(curFileSize)));
                    doc.add(Field.Text("type", lowerType));
                    doc.add(Field.Text("author", author));
                    doc.add(Field.Text("mod_date", dateStr));
                    doc.add(Field.Text("keywords", keyWords));
                    doc.add(Field.Text("title", curTitle));
                    doc.add(Field.Text("summary", curSummary));
                    if (documentText != null) {
                        doc.add(Field.Text("body", documentText));
                    }
                    else if (is != null) {
                        doc.add(Field.Text("body", new BufferedReader(new InputStreamReader(is))));
                    }
                    else {
                        logger.warn("addDocToIndex() text and stream are null");
                        doc.add(Field.Text("body", ""));
                    }
                    doc.add(Field.Text("URL", urlStr));
                    writer.addDocument(doc);
                    addToSummary(curTitle, author, dateStr, lowerType, curSummary, urlStr, Long.toString(curFileSize));
                }
                else {
                    ds.setStatus("DOCUMENT " + currentFi + " WAS NOT ADDED TO INDEX.");
                }

                // close stream if not null
                if (is != null) {
                    is.close();
                }
                // TODO remove temp file
            }
            catch (Exception e) {
                ds.setStatus("Error indexing " + currentFi + ":" + e.toString());
                logger.fatal("addDocToIndex() failed", e);
                returnInt = 1;
            }
            return returnInt;
        }
    }


    /**
     * The location of a URL in an index; used in the algorithm for updating an
     * index.
     * 
     * @return the location of the SpiderUrl in a web oriented DocSearcherIndex,
     *         or -1 if the URL is not in the index
     */
    public int spiderIndexNum(int lastFound, String fileName, IndexReader ir) {
        int returnInt = -1;
        synchronized (this) {
            if (lastFound == -1)
                lastFound = 0;
            try {
                Document doc;
                String compareName = "";
                int numDocs = ir.maxDoc();
                for (int i = lastFound; i < numDocs; i++) {
                    if (!ir.isDeleted(i)) {
                        doc = ir.document(i);
                        if (doc != null) {
                            compareName = doc.get("URL");
                            if (compareName.equals(fileName)) {
                                returnInt = i;
                                break;
                            }
                        }
                    }
                }
                if (returnInt == -1) {
                    for (int i = lastFound; i > 0; i--) {
                        if (!ir.isDeleted(i)) {
                            doc = ir.document(i);
                            if (doc != null) {
                                compareName = doc.get("URL");
                                // System.out.println("Comparing "+compareName+"
                                // to "+fileName);
                                if (compareName.equals(fileName)) {
                                    // System.out.println("MATCH FOUND AT "+i);
                                    returnInt = i;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (returnInt == -1)
                    ds.setStatus("File " + fileName + " not found in index!");
            } catch (Exception e) {
                logger.error("spiderIndexNum() failed", e);
                ds.setStatus("Error determining if doc is already in index!");
            }
            // finally {
            return returnInt;
            // }
        }
    }


    /**
     * Location of a file in a DocSearcher index; used by update algoritm to
     * update an index.
     * 
     * @return location of the document in the DocSearcherIndex or -1 if it is
     *         not in there
     */
    public int indexNum(int lastFound, String fileName, IndexReader ir) {
        int returnInt = -1;
        synchronized (this) {
            if (lastFound == -1)
                lastFound = 0;
            try {
                Document doc;
                String compareName = "";
                int numDocs = ir.maxDoc();
                for (int i = lastFound; i < numDocs; i++) {
                    if (!ir.isDeleted(i)) {
                        doc = ir.document(i);
                        if (doc != null) {
                            compareName = doc.get("path");
                            if (compareName.equals(fileName)) {
                                returnInt = i;
                                break;
                            }
                        }
                    }
                }
                if (returnInt == -1) {
                    for (int i = lastFound; i > 0; i--) {
                        if (!ir.isDeleted(i)) {
                            doc = ir.document(i);
                            if (doc != null) {
                                compareName = doc.get("path");
                                // System.out.println("Comparing "+compareName+"
                                // to "+fileName);
                                if (compareName.equals(fileName)) {
                                    // System.out.println("MATCH FOUND AT "+i);
                                    returnInt = i;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (returnInt == -1)
                    ds.setStatus("File " + fileName + " not found in index!");
            } catch (Exception e) {
                logger.error("indexNum() failed", e);
                ds.setStatus("Error determining if doc is already in index!");
            }
            return returnInt;
        }
    }


    /**
     * Updates a DocSearcherIndex
     *
     * @param di  DocSearcherIndex
     */
    public void updateIndex(DocSearcherIndex di) {
        notesBuf = new StringBuffer();
        newItsBuf = new StringBuffer();
        modItsItsBuf = new StringBuffer();
        delItsItsBuf = new StringBuffer();
        totalChanges = 0;
        long curFileSizeBytes = 0;
        int errNum = 0;
        StringBuffer noRobotsBuf = new StringBuffer();
        int numNoIndex = 0;
        // int numErrors = 0;
        StringBuffer failedBuf = new StringBuffer();
        int addedSuccessFully = 0;
        failedBuf.append("\n");
        synchronized (this) {
            if (di.isCdrom()) {
                // do nothing
            }
            else if (di.getIsSpider()) {
                doSpiderUpdate(di);
            }
            else if (! di.getPath().toLowerCase().endsWith(".zip")) { // not a zip
                                                                    // archive
                int numUpdates = 0;
                int numRemovals = 0;
                int numNew = 0;
                try {
                    IndexReader ir = IndexReader.open(di.getIndexPath());
                    int numDocs = ir.maxDoc();
                    ds.setStatus("There are " + numDocs + " docs in index " + di.getDescription() + "(" + di.getPath() + ")");
                    addHeader(di.getDescription());
                    ArrayList allDocsInIndex = new ArrayList(); // indexed files
                    // ArrayList allDocsInFolder = new ArrayList(); // current files
                    // ArrayList newDocsToAdd = new ArrayList(); // files to be added that are new
                    ds.setIsWorking(true);
                    ds.setProgressMax(numDocs);
                    ds.setCurProgressMSG("Updating Modified Files...");
                    setInsertMode(1); // note we are looking for modified files

                    logger.info("updateIndex() updating " + numDocs + " document from index");

                    for (int i = 0; i < numDocs; i++) {
                        if (! ds.getIsWorking()) {
                            break;
                        }
                        if (! ir.isDeleted(i)) {
                            ds.setCurProgress(i);
                            Document doc = ir.document(i);
                            if (doc != null) {
                                String curFiName = doc.get("path");
                                String curFiModDate = doc.get("mod_date");
                                File testFi = new File(curFiName);

                                // check file not found
                                if (testFi.exists()) {
                                    allDocsInIndex.add(curFiName);
                                    String realFileModDate = DateTimeUtils.getTimeStringForIndex(testFi.lastModified());

                                    // check file is changed
                                    if (! realFileModDate.equals(curFiModDate)) {
                                        logger.info("updateIndex() updating " + curFiName + " in index");
                                        
                                        numUpdates++;
                                        // remove old document
                                        ir.delete(i);
                                        ir.close();
                                        // open writer to add document once again
                                        ds.setStatus("Reindexing: " + curFiName);
                                        IndexWriter iw = new IndexWriter(di.getIndexPath(), new StandardAnalyzer(), false);
                                        // next line should remove too many files open errors
                                        // iw.setUseCompoundFile(true);
                                        addedSuccessFully = addDocToIndex(curFiName, iw, di, di.isCdrom(), null);
                                        iw.close();
                                        // reopen
                                        ir = IndexReader.open(di.getIndexPath());
                                        switch (addedSuccessFully) {
                                            case 1: // error
                                                errNum++;
                                                if (errNum < 8) {
                                                    failedBuf.append("\n");
                                                    failedBuf.append(curFiName);
                                                }
                                                ds.setStatus(DocSearch.dsErrIdxgFi + " " + curFiName);
                                                break;
                                            case 2: // meta robots = noindex
                                                numNoIndex++;
                                                if (numNoIndex < 8) {
                                                    noRobotsBuf.append("\n");
                                                    noRobotsBuf.append(curFiName);
                                                }
                                                ds.setStatus("No Indexing Meta Requirement found in : " + curFiName);
                                                break;
                                            default: // OK
                                                numUpdates++;
                                                ds.setStatus("Indexing " + curFiName + " complete.");
                                                break;
                                        } // end of switch
                                    }
                                }
                                else {
                                    ds.setStatus("Deleting: " + curFiName);
                                    logger.info("updateIndex() remove " + curFiName + " from index");
                                    ir.delete(i);
                                    addDelNote(doc);
                                    numRemovals++;
                                }
                            }
                        }
                        // end for not deleted
                        // else System.out.println("Document was null or
                        // deleted:"+i);
                    }
                    // end for getting gocs
                    ds.resetProgress();

                    // now add the new files
                    setInsertMode(0);
                    ArrayList folderList = new ArrayList();
                    folderList.add(di.getPath());
                    int startSubNum = Utils.countSlash(di.getPath());
                    int maxSubNum = startSubNum + di.getDepth();
                    int lastItemNo = 0;
                    int curItemNo = 0;
                    int lastFound = 0;
                    do {
                        // create our folder file
                        if (! ds.getIsWorking()) {
                            break;
                        }
                        String curFolderString = (String) folderList.get(curItemNo);
                        File curFolderFile = new File(curFolderString);
                        int curSubNum = Utils.countSlash(curFolderString);
                        // handle any subfolders --> add them to our folderlist
                        String[] foldersString = curFolderFile.list(DocSearch.ff);
                        int numFolders = foldersString.length;
                        for (int i = 0; i < numFolders; i++) {
                            // add them to our folderlist
                            String curFold = curFolderString + pathSep + foldersString[i] + pathSep;
                            curFold = Utils.replaceAll(pathSep + pathSep, curFold, pathSep);
                            folderList.add(curFold);
                            lastItemNo++;
                            // debug output
                        }
                        // end for having more than 0 folder
                        // add our files
                        String[] filesString = curFolderFile.list(DocSearch.wf);
                        int numFiles = filesString.length;
                        ds.setProgressMax(numDocs);
                        ds.setCurProgressMSG("Updating new Files...");
                        
                        for (int i = 0; i < numFiles; i++) {
                            // add them to our folderlist
                            if (! ds.getIsWorking()) {
                                break;
                            }
                            String curFi = curFolderString + pathSep + filesString[i];
                            curFi = Utils.replaceAll(pathSep + pathSep, curFi, pathSep);
                            curFileSizeBytes = FileUtils.getFileSize(curFi);
                            if (curFileSizeBytes > ds.getMaxFileSize()) {
                                ds.setStatus(DocSearch.dsFileTooBig + " (" + curFileSizeBytes + ") " + filesString[i]);
                            }
                            else {
                                lastFound = indexNum(lastFound, curFi, ir);
                                if (lastFound == -1) {
                                    logger.info("updateIndex() adding " + curFi + " to index");

                                    ir.close();
                                    // open writer to add document once again
                                    IndexWriter iw = new IndexWriter(di.getIndexPath(), new StandardAnalyzer(), false);
                                    addedSuccessFully = addDocToIndex(curFi, iw, di, di.isCdrom(), null);
                                    switch (addedSuccessFully) {
                                        case 1: // error
                                            errNum++;
                                            if (errNum < 8) {
                                                failedBuf.append("\n");
                                                failedBuf.append(curFi);
                                            }
                                            ds.setStatus(DocSearch.dsErrIdxg + " " + curFi);
                                            break;
                                        case 2: // meta robots = noindex
                                            numNoIndex++;
                                            if (numNoIndex < 8) {
                                                noRobotsBuf.append("\n");
                                                noRobotsBuf.append(curFi);
                                            }
                                            ds.setStatus("Document Exlusion (robots = NOINDEX) : " + curFi);
                                            break;
                                        default: // OK
                                            numNew++;
                                            ds.setStatus("New Document Added : " + curFi);
                                            break;
                                    } // end of switch
                                    iw.close();
                                    // reopen
                                    ir = IndexReader.open(di.getIndexPath());
                                } // end for lastfound not -1
                            } // end for file size not too big
                            ds.setCurProgress(i);
                            ds.resetProgress();
                        }
                        // end for having more than 0 folder
                        // increment our curItem
                        folderList.set(curItemNo, null); // remove memory overhead as you go!
                        curItemNo++;
                        if (curSubNum >= maxSubNum){
                            break;
                        }
                        if (! ds.getIsWorking()) {
                            break;
                        }
                    }
                    while (curItemNo <= lastItemNo);
                    //
                    ir.close(); // always close!
                    StringBuffer updateMSGBuf = new StringBuffer();
                    updateMSGBuf.append('\n');
                    updateMSGBuf.append(numRemovals);
                    updateMSGBuf.append(" files were removed from index.");
                    updateMSGBuf.append('\n');
                    updateMSGBuf.append(numUpdates);
                    updateMSGBuf.append(" files were reindexed.");
                    updateMSGBuf.append('\n');
                    updateMSGBuf.append(numNew);
                    updateMSGBuf.append(" new files were added to the index.");
                    updateMSGBuf.append('\n');
                    //
                    totalChanges = numRemovals + numUpdates + numNew;
                    // all our stuff to the notesBuf
                    addNote(updateMSGBuf.toString(), "", true);
                    // add our new and modified files
                    if (numNew > 0) {
                        addNote(Messages.getString("DocSearch.newFiles"), "", true);
                        notesBuf.append(newItsBuf);
                    }
                    //
                    if (numUpdates > 0) {
                        addNote(Messages.getString("DocSearch.updatedFiles"), "", true);
                        notesBuf.append(modItsItsBuf);
                    }
                    //
                    // 
                    if (numRemovals > 0) {
                        addNote(Messages.getString("DocSearch.deletedFiles"), "", true);
                        notesBuf.append(delItsItsBuf);
                    }
                    //

                    addFooter();
                    if (errNum == 0) {
                        updateMSGBuf.append("No errors were encountered during this process.");
                        if (numNoIndex > 0) {
                            updateMSGBuf.append("\n\n").append(numNoIndex).append(" files were not indexed due to meta data constraints (robots = NOINDEX), including:\n");
                            updateMSGBuf.append(noRobotsBuf);
                        }
                        ds.showMessage("Update of index " + di.getDescription() + " Completed", updateMSGBuf.toString());
                    } else {
                        updateMSGBuf.append(errNum).append(" errors were encountered during this process.\nThe following files had problems being indexed or re-indexed:\n").append(failedBuf);
                        if (numNoIndex > 0) {
                            updateMSGBuf.append("\n\n").append(numNoIndex).append(" files were not indexed due to meta data constraints (robots = NOINDEX), including:\n");
                            updateMSGBuf.append(noRobotsBuf);
                        }

                        ds.showMessage("Errors during Update of index " + di.getDescription(), updateMSGBuf.toString());
                    }
                }
                // end of try
                catch (Exception e) {
                    logger.error("updateIndex() error during update index " + di.getDescription(), e);
                    ds.showMessage("Error updating index " + di.getDescription(), e.toString());
                }

                addFooter();
                di.setLastIndexed(DateTimeUtils.getToday());
                ds.setStatus("Update of index " + di.getDescription() + " completed.");
                ds.setIsWorking(false);
            }
            else {
                ds.doZipArchiveUpdate(di);
            }
        }
    }


    /**
     * Short summary description of a document - obtained programmatically based
     * upon the type of file.
     * 
     * @return short summary for a file
     */
    private String getDocSummary(String fileName, int type) {
        String returnString = "Untitled";

        switch (type) {
            case FileType.HTML: // HTML
                returnString = getHtmlSummary(fileName);
                break;
            default: // all other
                returnString = getTextSummary(fileName);
                break;
        }

        return returnString;
    }


    /**
     * Title for a file
     * 
     * @return title for a file
     */
    private String getTitle(String fileName) {
        int lastSlash = fileName.lastIndexOf(pathSep);
        boolean foundFileTitle = false;
        String newTitle = "Untitled";
        int fileLen = fileName.length();
        int fileTypeEnding = fileName.lastIndexOf(".");
        if (lastSlash != -1) {
            lastSlash++;
            if (fileTypeEnding > lastSlash)
                newTitle = fileName.substring(lastSlash, fileTypeEnding);
            else
                newTitle = fileName.substring(lastSlash, fileLen);
        } else {
            lastSlash = fileName.lastIndexOf("\\");
            if (lastSlash != -1) {
                lastSlash++;
                if (fileTypeEnding > lastSlash)
                    newTitle = fileName.substring(lastSlash, fileTypeEnding);
                else
                    newTitle = fileName.substring(lastSlash, fileLen);
            }
            // end for windows file or URL
        }
        if (newTitle.length() != 0) {
            newTitle = Utils.replaceAll("_", newTitle, " ").trim();
            foundFileTitle = true;
        }
        if (!foundFileTitle)
            return fileName;
        return newTitle;
    }


    /**
     * The short summary generated for a text based file
     * 
     * @return summary for a text file
     */
    public String getTextSummary(String fileName) {
        String returnString = "No Summary";

        Reader inputReader = null;
        try {
            inputReader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)));

            int ch;
            char curChar = ' ';
            int maxTitleLen = 286;
            int curCharNum = 0;
            char lastChar = ' ';
            boolean skipChar = false;
            int numLines = 0;
            StringBuffer titleBuf = new StringBuffer();

            while ((ch = inputReader.read()) > -1) {
                curChar = (char) ch;

                // append to our title
                skipChar = false;
                if (curChar == '\n' || curChar == '\r') {
                    curChar = ' ';
                }
                if (curChar == ' ' && lastChar == ' ') {
                    skipChar = true;
                }
                if (! skipChar) {
                    lastChar = curChar;
                    curCharNum++;
                    titleBuf.append(curChar);
                }
                if (numLines > 3 || curCharNum > maxTitleLen) {
                    break;
                }
            }
            String newTitle = titleBuf.toString().trim();
            if (newTitle.length() >= 4) {
                returnString = newTitle + "...";
            }
            else {
                returnString = getTitle(fileName);
            }
        }
        catch (IOException ioe) {
            logger.error("getTextSummary() failed", ioe);
            ds.setStatus("Error obtaining file title: " + fileName);
        }
        finally {
            try {
                if (inputReader != null) {
                    inputReader.close();
                }
            }
            catch (IOException ioe) {
                logger.error("getTextSummary() can't close Reader", ioe);
            }
        }

        return returnString;
    }


    /**
     * Short summary for a web page file
     * 
     * @return web page summary
     */
    private String getHtmlSummary(String fileName) {
        String returnString = getMetaTag(fileName, "description");
        if (returnString.equals("")) {
            returnString = getMetaTag(fileName, "summary");
        }
        return returnString;
    }


    /**
     * Meta Tag Content given a specific metaTag in a file
     * 
     * @return meta tag content
     */
    private String getMetaTag(String fileName, String metaTag) {
        String lowerMetaTag = metaTag.toLowerCase();
        String returnString = "";
        File file = new File(fileName);
        try {
            FileInputStream fi = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(fi);
            Reader in = new BufferedReader(isr);
            int curI = 0; // reset i
            char curChar = ' ';
            // byte curBint;
            // int maxTitleLen = 36;
            int curCharNum = 0;
            char lastChar = ' ';
            boolean skipChar = false;
            // int numLines = 0;
            StringBuffer tagBuf = new StringBuffer();
            boolean inTag = false;
            // boolean inTitle = false;
            String tagString = "";
            String lowerTag = "";
            String attr = "";
            String lowerAttr = "";
            while (curI != -1) {
                curI = in.read();
                if (curI != -1) {
                    curChar = (char) curI;
                    // append to our title
                    skipChar = false;
                    if ((curChar == '\n') || (curChar == '\r'))
                        curChar = ' ';
                    curCharNum++;
                    if (curChar == '<')
                        inTag = true;
                    if (curChar == '>') {
                        tagBuf.append(curChar);
                        inTag = false;
                        tagString = tagBuf.toString();
                        lowerTag = tagString.toLowerCase();
                        if (lowerTag.startsWith("<meta")) {
                            attr = Utils.getTagString("name=", tagString);
                            lowerAttr = attr.toLowerCase().trim();
                            if (lowerAttr.equals(lowerMetaTag)) {
                                returnString = Utils.getTagString("content=", tagString);
                                logger.debug("getMetaTag() " + fileName + " has " + returnString + "\n for a " + lowerMetaTag);
                                break;
                            }
                        }
                        if (lowerTag.startsWith("<body"))
                            break;
                        tagBuf = new StringBuffer();
                    }
                    if ((curChar == ' ') && (lastChar == ' '))
                        skipChar = true;
                    if (!skipChar)
                        lastChar = curChar;
                    if (inTag)
                        tagBuf.append(curChar);
                } else
                    break;
            }

            fi.close();
            isr.close();
            in.close();
        } catch (Exception eF) {
            ds.setStatus("Error obtaining file author: " + fileName);
        }
        return returnString;
    }


    /**
     * Author of a webpage, using author or webmaster attribute
     * 
     * @return author of a webpage
     */
    private String getAuthor(String fileName) {
        String returnString = "";
        File file = new File(fileName);
        try {
            FileInputStream fi = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(fi);
            Reader in = new BufferedReader(isr);
            int curI = 0; // reset i
            char curChar = ' ';
            // byte curBint;
            // int maxTitleLen = 36;
            int curCharNum = 0;
            char lastChar = ' ';
            boolean skipChar = false;
            // int numLines = 0;
            StringBuffer tagBuf = new StringBuffer();
            boolean inTag = false;
            // boolean inTitle = false;
            String tagString = "";
            String lowerTag = "";
            String attr = "";
            String lowerAttr = "";
            while (curI != -1) {
                curI = in.read();
                if (curI != -1) {
                    curChar = (char) curI;
                    // append to our title
                    skipChar = false;
                    if ((curChar == '\n') || (curChar == '\r'))
                        curChar = ' ';
                    curCharNum++;
                    if (curChar == '<')
                        inTag = true;
                    if (curChar == '>') {
                        tagBuf.append(curChar);
                        inTag = false;
                        tagString = tagBuf.toString();
                        lowerTag = tagString.toLowerCase();
                        if (lowerTag.startsWith("<meta")) {
                            attr = Utils.getTagString("name=", tagString);
                            lowerAttr = attr.toLowerCase();
                            if ((lowerAttr.indexOf("author") != -1) || (lowerAttr.indexOf("webmaster") != -1)) {
                                returnString = Utils.getTagString("content=", tagString);
                                break;
                            }
                        }
                        if (lowerTag.startsWith("<body"))
                            break;
                        tagBuf = new StringBuffer();
                    }
                    if ((curChar == ' ') && (lastChar == ' '))
                        skipChar = true;
                    if (!skipChar)
                        lastChar = curChar;
                    if (inTag)
                        tagBuf.append(curChar);
                } else
                    break;
            }
            fi.close();
            in.close();
            isr.close();
        } catch (Exception eF) {
            ds.setStatus("Error obtaining file author: " + fileName);
        }
        return returnString;
    }


    /**
     * Title of a document, varies by type of document
     * 
     * @return document title
     */
    private String getDocTitle(String fileName, int type) {
        if (logger.isDebugEnabled()) {
            logger.debug("getDocTitle('" + fileName + "', '" + type + "') entered");
        }
        String returnString = "Untitled";

        // TODO !! check method getHtmlTitle + getTextTitle + getTitle

        switch (type) {
            case FileType.HTML: // HTML
                returnString = getHtmlTitle(fileName);
                break;
            case FileType.TEXT: // text
            case FileType.OO_WRITER: // oo text
            case FileType.OO_IMPRESS: // oo impress
            case FileType.OO_CALC: // oo calc
            case FileType.OO_DRAW: // oo draw
                returnString = getTextTitle(fileName);
                break;
            default: // all other
                returnString = getTitle(fileName);
                break;
        }

        return returnString;
    }


    /**
     * Title of a web page
     * 
     * @return title of the web page
     */
    private String getHtmlTitle(String fileName) {
        String returnString = "Untitled";
        File file = new File(fileName);
        try {
            FileInputStream fi = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(fi);
            Reader in = new BufferedReader(isr);
            int curI = 0; // reset i
            char curChar = ' ';
            // byte curBint;
            // int maxTitleLen = 36;
            int curCharNum = 0;
            char lastChar = ' ';
            boolean skipChar = false;
            // int numLines = 0;
            StringBuffer tagBuf = new StringBuffer();
            boolean inTag = false;
            boolean inTitle = false;
            String tagString = "";
            String lowerTag = "";
            StringBuffer titleBuf = new StringBuffer();
            while (curI != -1) {
                curI = in.read();
                if (curI != -1) {
                    curChar = (char) curI;
                    // append to our title
                    skipChar = false;
                    if ((curChar == '\n') || (curChar == '\r'))
                        curChar = ' ';
                    curCharNum++;
                    if (curChar == '<') {
                        inTag = true;
                        if (inTitle)
                            break;
                    }
                    if (curChar == '>') {
                        tagBuf.append(curChar);
                        inTag = false;
                        tagString = tagBuf.toString();
                        lowerTag = tagString.toLowerCase();
                        if (lowerTag.startsWith("<titl"))
                            inTitle = true;
                        else if (lowerTag.startsWith("</head"))
                            break;
                        else if (lowerTag.startsWith("<body"))
                            break;
                        tagBuf = new StringBuffer();
                    }
                    // end for end of a tag

                    if ((curChar == ' ') && (lastChar == ' '))
                        skipChar = true;
                    if (!skipChar)
                        lastChar = curChar;
                    if (inTag)
                        tagBuf.append(curChar);
                    else if (inTitle) {
                        if ((!skipChar) && (curChar != '>'))
                            titleBuf.append(curChar);
                    }
                } else
                    break;
            }
            fi.close();
            in.close();
            isr.close();
            String newTitle = titleBuf.toString().trim();
            if (newTitle.length() >= 4)
                returnString = newTitle;
        }
        // end of trying to catch file
        catch (Exception eF) {
            ds.setStatus("Error obtaining file title: " + fileName);
        }
        return returnString;
    }


    /**
     * Title of a text file
     * 
     * @return title created from a text file
     */
    private String getTextTitle(String fileName) {
        String returnString = "Untitled";
        File file = new File(fileName);
        try {
            FileInputStream fi = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(fi);
            Reader in = new BufferedReader(isr);
            int curI = 0; // reset i
            char curChar = ' ';
            // byte curBint;
            int maxTitleLen = 36;
            int curCharNum = 0;
            char lastChar = ' ';
            boolean skipChar = false;
            int numLines = 0;
            StringBuffer titleBuf = new StringBuffer();
            while (curI != -1) {
                curI = in.read();
                if (curI != -1) {
                    curChar = (char) curI;
                    // append to our title
                    skipChar = false;
                    if ((curChar == '\n') || (curChar == '\r'))
                        curChar = ' ';
                    if ((curChar == ' ') && (lastChar == ' '))
                        skipChar = true;
                    if (!skipChar) {
                        lastChar = curChar;
                        curCharNum++;
                        titleBuf.append(curChar);
                    }
                    if ((numLines > 3) || (curCharNum > maxTitleLen))
                        break;
                } else
                    break;
            }
            String newTitle = titleBuf.toString().trim();
            if (newTitle.length() >= 4)
                returnString = newTitle + "...";
            else
                returnString = getTitle(fileName);
            fi.close();
            in.close();
            isr.close();
        } catch (Exception eF) {
            ds.setStatus("Error obtaining file title: " + fileName);
        }
        return returnString;
    }


    /**
     * Strips all markup from a markup based file such as HTML or XML and writes
     * the results to newFileName
     */
    private void removeAllTags(String originalFile, String newFileName) throws IOException {
        boolean inTag = false;
        File origFile = new File(originalFile);
        FileInputStream fi = new FileInputStream(origFile);
        InputStreamReader isr = new InputStreamReader(fi);
        FileWriter filewriter = new FileWriter(newFileName);
        PrintWriter pw = new PrintWriter(filewriter);
        // StringBuffer tagBuf = new StringBuffer();
        StringBuffer nonTagTextf = new StringBuffer();
        String t = "";
        // int curI = 0; // reset i
        // byte rB;
        // byte curBint;
        char curChar = ' ';
        Reader in = new BufferedReader(isr);
        int ch;
        while ((ch = in.read()) > -1) {
            curChar = (char) ch;
            if (curChar == '>') {
                inTag = false;
                nonTagTextf = new StringBuffer();
            } else if (curChar == '<') {
                inTag = true;
                t = nonTagTextf.toString().trim();
                if (t.length() > 0) {
                    pw.println(t);
                }
            }
            if ((!inTag) && (curChar != '>')) {
                nonTagTextf.append(curChar);
            }
        }

        fi.close();
        in.close();
        filewriter.close();
        pw.close();
    }


    /**
     * Searches a file for a tag delimitted content
     * 
     * @return contents of a tag given a tagPrefix and a fileName
     */
    private String getTagText(String tagPrefix, String fileName) throws IOException {
        tagPrefix = tagPrefix.toLowerCase();
        // String tagStart = "<" + tagPrefix;
        String tagEnd = "</";
        StringBuffer retBuf = new StringBuffer();
        File origFile = new File(fileName);
        FileInputStream fi = new FileInputStream(origFile);
        InputStreamReader isr = new InputStreamReader(fi);
        Reader in = new BufferedReader(isr);
        int curI = 0; // reset i
        // byte rB;
        // byte curBint;
        char curChar = ' ';
        StringBuffer tagBuf = new StringBuffer();
        StringBuffer nonTagTextf = new StringBuffer();
        boolean readContent = false;
        boolean inTag = false;
        String tagStr = "";
        while (curI != -1) {
            curI = in.read();
            if (curI != -1) {
                // curBint = (byte)curI;
                curChar = (char) curI;
                if (curChar == '>') {
                    tagStr = tagBuf.toString().toLowerCase();
                    if ((tagStr.indexOf("/") == -1) && (tagStr.indexOf(tagPrefix) != -1)) { // (tagStr.startsWith(tagStart))
                        readContent = true;
                    }
                    if ((tagStr.startsWith(tagEnd)) && (tagStr.indexOf(tagPrefix) != -1)) {
                        retBuf.append(nonTagTextf.toString());
                        logger.debug("getTagText() Value for " + tagPrefix + " is " + nonTagTextf.toString() + " in " + fileName);
                        break;
                    }
                    tagBuf = new StringBuffer();
                    inTag = false;
                } else if (curChar == '<')
                    inTag = true;
                if (inTag)
                    tagBuf.append(curChar);
                else if ((readContent) && (curChar != '>'))
                    nonTagTextf.append(curChar);
                else if ((readContent) && (curChar == '>'))
                    nonTagTextf.append(" ");
            } else
                break;
        }
        fi.close();
        isr.close();
        in.close();
        return retBuf.toString();
    }


    /**
     * Notes generating during an index update process.
     * 
     * @return notes that indicate how an index update process went
     */
    public StringBuffer getUpDateNotes() {
        return notesBuf;
    }


    /**
     * Populates the notes during an index update.
     */
    public void addNote(String message, String link, boolean newLine) {
        boolean useLink = true;
        if (link.equals(""))
            useLink = false;
        if (doEmail) {
            if (isTextEmailFormat) {
                notesBuf.append(message);
            } // end of text format
            else {
                if (newLine)
                    notesBuf.append("<p align=\"left\">");
                message = Utils.replaceAll("\n", message, "<br>");
                if (useLink) {
                    notesBuf.append("<a href=\"");
                    notesBuf.append(link);
                    notesBuf.append("\">");
                }
                notesBuf.append(message);
                if (useLink)
                    notesBuf.append("</a>");
                if (newLine)
                    notesBuf.append("</p>");
            }
            if (newLine)
                notesBuf.append("\n");
        }
    }


    /**
     * Tells docSearch that an email should be generated for an index update
     * process.
     */
    public void setDoEmail(boolean toSet) {
        doEmail = toSet;
    }


    /**
     * html content to close out an HTML based email update is added to the
     * notes of an update process
     */
    public void addFooter() {
        if (doEmail) {
            if (isTextEmailFormat) {
                notesBuf.append("\n");
            } // end of text format
            else {
                notesBuf.append("</BODY></HTML>");
                notesBuf.append("\n");
            }
        }
    }


    /**
     * html content to begin an HTML based email update is added to the notes of
     * an update process
     */
    public void addHeader(String title) {
        if (doEmail) {
            if (isTextEmailFormat) {
                notesBuf.append(title);
                notesBuf.append("\n");
            } // end of text format
            else {
                notesBuf.append("<HTML><HEAD><TITLE>");
                notesBuf.append(title);
                notesBuf.append("</TITLE></HEAD><BODY><h3>");
                notesBuf.append(title);
                notesBuf.append("</h3>");
                notesBuf.append("\n");
            }
        }
    }


    /**
     * indicates that index update email should be set to text if true or HTML
     * if false
     */
    public void setEmailText(boolean isEmail) {
        isTextEmailFormat = isEmail;
    }


    /**
     * adds a note about a modified document to the report (notes) for an index
     * update
     */
    public void addToSummary(String title, String author, String dateStr, String lowerType, String curSummary, String urlStr, String curFileSize) {
        if (logger.isDebugEnabled()) {
            logger.debug("addToSummry() \ntitle='" + title + "' \ncurSummary='" + curSummary + "' \nurlStr='" + urlStr + "' \nlowerType='" + lowerType + "'");
        }
        int curInsrtMd = getInsertMode();
        if (doEmail) {
            // TEXT
            if (isTextEmailFormat) { // 0 =new, 1= mod
                switch (curInsrtMd) {
                    case 1: //
                        modItsItsBuf.append('\n');
                        modItsItsBuf.append(title);
                        modItsItsBuf.append('\n');
                        modItsItsBuf.append(curSummary);
                        modItsItsBuf.append('\n');
                        modItsItsBuf.append(urlStr);
                        modItsItsBuf.append('\n');
                        modItsItsBuf.append(author);
                        modItsItsBuf.append(", ");
                        modItsItsBuf.append(curFileSize);
                        modItsItsBuf.append(", ");
                        modItsItsBuf.append(lowerType);
                        modItsItsBuf.append('\n');
                        break;
                    default: // new
                        newItsBuf.append('\n');
                        newItsBuf.append(title);
                        newItsBuf.append('\n');
                        newItsBuf.append(curSummary);
                        newItsBuf.append('\n');
                        newItsBuf.append(urlStr);
                        newItsBuf.append('\n');
                        newItsBuf.append(author);
                        newItsBuf.append(", ");
                        newItsBuf.append(curFileSize);
                        newItsBuf.append(", ");
                        newItsBuf.append(lowerType);
                        newItsBuf.append('\n');
                        break;
                }
            } else {
                // HTML
                switch (curInsrtMd) {
                    case 1: //
                        modItsItsBuf.append("<p align=\"left\"><a href=\"");
                        modItsItsBuf.append(urlStr);
                        modItsItsBuf.append("\"><b>");
                        modItsItsBuf.append(title);
                        modItsItsBuf.append("</b></a><br>");
                        modItsItsBuf.append(curSummary);
                        modItsItsBuf.append("<br>");
                        modItsItsBuf.append(urlStr);
                        modItsItsBuf.append("<br>");
                        modItsItsBuf.append(author);
                        modItsItsBuf.append(", ");
                        modItsItsBuf.append(curFileSize);
                        modItsItsBuf.append(", ");
                        modItsItsBuf.append(lowerType);
                        modItsItsBuf.append("</p>");
                        break;
                    default: // new
                        newItsBuf.append("<p align=\"left\"><a href=\"");
                        newItsBuf.append(urlStr);
                        newItsBuf.append("\"><b>");
                        newItsBuf.append(title);
                        newItsBuf.append("</b></a><br>");
                        newItsBuf.append(curSummary);
                        newItsBuf.append("<br>");
                        newItsBuf.append(urlStr);
                        newItsBuf.append("<br>");
                        newItsBuf.append(author);
                        newItsBuf.append(", ");
                        newItsBuf.append(curFileSize);
                        newItsBuf.append(", ");
                        newItsBuf.append(lowerType);
                        newItsBuf.append("</p>");
                        break;
                }
            }
        }
    }


    /**
     * Used by update process to determine if documents being indexed are new,
     * modified or deleted - so that appropriate notes can be added to the
     * summary report of the index update process
     * 
     * @return 0 = new, 1 = modified, 2 = deleted
     */
    private int getInsertMode() {
        return insertMode;
    }


    /**
     * Adds a note about a file that can no longer be found - for a specific
     * index (during an update process)
     */
    public void addDelNote(Document doc) {
        //int curInsrtMd=getInsertMode();
        String title = doc.get("title");
        String author = doc.get("author");
        String urlStr = doc.get("url");
        String curSummary = doc.get("summary");
        String curFileSize = doc.get("size");
        String lowerType = doc.get("type");
        if (doEmail) {
            // TEXT
            if (isTextEmailFormat) { // 0 =new, 1= mod
                delItsItsBuf.append("\n");
                delItsItsBuf.append(title);
                delItsItsBuf.append("\n");
                delItsItsBuf.append(curSummary);
                delItsItsBuf.append("\n");
                delItsItsBuf.append(urlStr);
                delItsItsBuf.append("\n");
                delItsItsBuf.append(author);
                delItsItsBuf.append(", ");
                delItsItsBuf.append(curFileSize);
                delItsItsBuf.append(", ");
                delItsItsBuf.append(lowerType);
                delItsItsBuf.append("\n");
            } // end for text
            else { // html email format
                delItsItsBuf.append("<p align=\"left\"><a href=\"");
                delItsItsBuf.append(urlStr);
                delItsItsBuf.append("\"><b>");
                delItsItsBuf.append(title);
                delItsItsBuf.append("</b></a><br>");
                delItsItsBuf.append(curSummary);
                delItsItsBuf.append("<br>");
                delItsItsBuf.append(urlStr);
                delItsItsBuf.append("<br>");
                delItsItsBuf.append(author);
                delItsItsBuf.append(", ");
                delItsItsBuf.append(curFileSize);
                delItsItsBuf.append(", ");
                delItsItsBuf.append(lowerType);
                delItsItsBuf.append("</p>");
            }
        } // end for doEmail
    }


    /**
     * sets the mode for which notes are made during an update to an index
     */
    public void setInsertMode(int toSet) {
        insertMode = toSet;
    }


    /**
     * Total number of changes made during an index update process.
     * 
     * @return the number of changes made to a DocSearcherIndex during an update
     *         of that index
     */
    public int getTotalChanges() {
        return totalChanges;
    }


    /**
     * Obtains Meta Data for a web page
     * 
     * @param filename  filename of webpage
     * @return author, title, and summary of a web page speficied in filename
     */
    public WebPageMetaData getWebPageMetaData(String filename) {
        WebPageMetaData tempWpmd = new WebPageMetaData();
        tempWpmd.setFilename(filename);

        BufferedReader reader = null;
        PrintWriter writer = null;
        try {
            boolean inTag = false;
            boolean foundSummary = false;
            boolean inBody = false;
            boolean inScript = false;
            boolean inTitle = false;

            StringBuffer tagBuf = new StringBuffer();
            StringBuffer titleBuf = new StringBuffer();
            StringBuffer summaryBuf = new StringBuffer();

            // open reader and writer
            File origFile = new File(filename);
            reader = new BufferedReader(new InputStreamReader(new FileInputStream(origFile)));
            writer = new PrintWriter(new FileWriter(ds.htmlTextFile));
            
            StringBuffer nonTagTextf = new StringBuffer();
            int curBodyNonTagTextNum = 0;
            int sumMaxSize = 220;
            int ch;

            // step during html source
            while ((ch = reader.read()) > -1) {
                char curChar = (char) ch;

                if (curChar == '>') {
                    inTag = false;
                    //
                    tagBuf.append(curChar);
                    String realTag = tagBuf.toString();
                    String lowerTag = realTag.toLowerCase();
                    if (lowerTag.startsWith(META_TAG)) {
                        String tempMetaName = Utils.getTagString("name=", lowerTag);
                        if (tempMetaName.startsWith("description")) {
                            String tempMetaContent = Utils.getTagString("content=", realTag);
                            if (! tempMetaContent.trim().equals("")) {
                                tempWpmd.setDescription(tempMetaContent);
                                foundSummary = true;
                            }
                        }
                        else if (tempMetaName.startsWith("summary")) {
                            String tempMetaContent = Utils.getTagString("content=", realTag);
                            if (! tempMetaContent.trim().equals("")) {
                                tempWpmd.setDescription(tempMetaContent);
                                foundSummary = true;
                            }
                        }
                        else if (tempMetaName.startsWith("author") || tempMetaName.indexOf("webmaster") != -1) {
                            String tempMetaContent = Utils.getTagString("content=", realTag);
                            tempWpmd.setAuthor(tempMetaContent);
                        }
                    }
                    else if (lowerTag.startsWith(SCRIPT_TAG)) {
                        if (!lowerTag.endsWith("/>")) {
                            inScript = true;
                        }
                    }
                    else if (lowerTag.startsWith(SCRIPT_TAG_END)) {
                        inScript = false;
                    }
                    else if (lowerTag.startsWith(BODY_TAG)) {
                        inBody = true;
                    }
                    else if (lowerTag.startsWith(BODY_TAG_END)) {
                        inBody = false;
                    }
                    else if (lowerTag.startsWith(TITLE_TAG)) {
                        inTitle = true;
                    }
                    else if (lowerTag.startsWith(TITLE_TAG_END)) {
                        inTitle = false;
                        tempWpmd.setTitle(titleBuf.toString());
                    }
                    // reset our buffers
                    tagBuf = new StringBuffer();
                    nonTagTextf = new StringBuffer();
                }
                else if (curChar == '<') {
                    inTag = true;
                    tagBuf = new StringBuffer();
                    String t = nonTagTextf.toString().trim();
                    int tSize = t.length();
                    if (tSize > 0) {
                        if (! inScript && inBody) {
                            writer.println(t);
                        }
                    }
                    nonTagTextf = new StringBuffer();
                    //
                    if (! foundSummary) {
                        // 
                        if (inBody) {
                            curBodyNonTagTextNum += tSize;
                            summaryBuf.append(' ');
                            summaryBuf.append(t);
                            summaryBuf.append(' ');
                            if (curBodyNonTagTextNum >= sumMaxSize) {
                                tempWpmd.setDescription(Utils.concatStrToEnd(summaryBuf.toString(), sumMaxSize));
                                foundSummary = true;
                            }
                        }
                    }
                    //
                } // end for the beginning of a tag
                if (inTitle && curChar != '>' && ! inTag) {
                    titleBuf.append(curChar);
                }
                else if (! inTag && curChar != '>') {
                    nonTagTextf.append(curChar);
                }
                else if (inTag) {
                    tagBuf.append(curChar);
                }
            } // end for while reading

            if (! foundSummary && curBodyNonTagTextNum > 0) {
                tempWpmd.setDescription(summaryBuf.toString());
            }
        }
        catch (IOException ioe) {
            logger.error("getWebPageMetaData() failed", ioe);
            ds.setStatus(DocSearch.dsErr + " : " + ioe.toString());
        }
        finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            }
            catch (IOException ioe) {
                logger.fatal("getWebPageMetaData() can't close BufferedReader", ioe);
            }

            if (writer != null) {
                 writer.close();
            }
        }

        return tempWpmd;
    }


    /**
     * Updates a spidered DocSearcherIndex
     */
    public void doSpiderUpdate(DocSearcherIndex idx) {
        // updates an index that is spider based
        int maxDocsToGet = idx.getDepth();
        int percentGrowth = 10;
        int pcntNum = maxDocsToGet / percentGrowth;

        // allow spidered indexes to grow by 10 percent
        if (pcntNum > 0) {
            maxDocsToGet += pcntNum;
        }
        ds.setStatus(DocSearch.plsWait + " " + DocSearch.waitForIndexUpDate + " " + idx.getDescription());

        // load the list of previously found links
        String linksListName = FileUtils.addFolder(fEnv.getIndexDirectory(), Utils.replaceAll(" ", idx.getDescription(), "_") + ".txt");
        ArrayList oldSpiderLinks = Utils.getSpiderLinks(linksListName);

        logger.debug("doSpiderUpdate() Previously found link num total=" + oldSpiderLinks.size());

        LinkFinder ulf = new LinkFinder(idx.getPath(), linksListName, idx.getDepth(), ds, idx, oldSpiderLinks);
        ulf.init();
        try {
            ulf.update();
        }
        catch (IOException ioe) {
            logger.fatal("doSpiderUpdate() failed with IOException", ioe);
            ds.showMessage(DocSearch.dsErr, ioe.toString());
        }

        int numNew = ulf.getNumNew();
        int numDeletes = ulf.getNumDeletes();
        int numMetaNoIdx = ulf.getNumMetaNoIdx();
        int numChanges = ulf.getNumUpdates();
        int numUnChanged = ulf.getNumUnchanged();
        int numFails = ulf.getNumFails();

        StringBuffer resultsMessage = new StringBuffer();
        resultsMessage.append(numNew).append(' ').append(DocSearch.dsNumNewFiles).append("\n\n");
        resultsMessage.append(numDeletes).append(' ').append(DocSearch.dsNumDelFiles).append("\n\n");
        resultsMessage.append(numChanges).append(' ').append(DocSearch.dsNumchangedFiles).append("\n\n");
        resultsMessage.append(numUnChanged).append(' ').append(DocSearch.dsNumUnchangedFiles).append("\n\n");
        resultsMessage.append(numMetaNoIdx).append(' ').append(DocSearch.dsNotIdxdMeta).append("\n\n");
        resultsMessage.append(numFails).append(' ').append(DocSearch.dsFailIdxDocs).append("\n\n");
        int numTotalDocs = numUnChanged + numNew - numFails;
        resultsMessage.append(numTotalDocs).append(' ').append(DocSearch.dsTtlDxInIdx).append("\n\n");

        ds.showMessage(idx.getDescription() + " " + DocSearch.dsUpdts, resultsMessage.toString());
    }
} 
