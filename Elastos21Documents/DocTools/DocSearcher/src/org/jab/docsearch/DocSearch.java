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

import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.print.PageFormat;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.lang.reflect.InvocationTargetException;
import java.net.InetAddress;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Properties;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JEditorPane;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.border.TitledBorder;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;
import javax.swing.text.html.HTMLFrameHyperlinkEvent;

import org.apache.log4j.Logger;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.DateFilter;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;

import org.jab.docsearch.constants.FileType;
import org.jab.docsearch.constants.OSType;
import org.jab.docsearch.filters.FolderFilter;
import org.jab.docsearch.filters.GenericFilter;
import org.jab.docsearch.gui.CdAssistantDialog;
import org.jab.docsearch.gui.DocSplashViewer;
import org.jab.docsearch.gui.DsProperties;
import org.jab.docsearch.gui.ImportDialog;
import org.jab.docsearch.gui.JComponentVista;
import org.jab.docsearch.gui.ManageIndexesDialog;
import org.jab.docsearch.gui.ManifestDialog;
import org.jab.docsearch.gui.MessageConfirmRunner;
import org.jab.docsearch.gui.MessageRunner;
import org.jab.docsearch.gui.NewBookmarkDialog;
import org.jab.docsearch.gui.NewIndexDialog;
import org.jab.docsearch.gui.ProgressPanel;
import org.jab.docsearch.gui.SpiderDialog;
import org.jab.docsearch.spider.LinkFinder;
import org.jab.docsearch.threads.EmailThread;
import org.jab.docsearch.threads.GuiThread;
import org.jab.docsearch.threads.ThreadedSearch;
import org.jab.docsearch.utils.ArchiveMetaData;
import org.jab.docsearch.utils.DateTimeUtils;
import org.jab.docsearch.utils.FileTypeUtils;
import org.jab.docsearch.utils.FileUtils;
import org.jab.docsearch.utils.LogAnalysis;
import org.jab.docsearch.utils.Logging;
import org.jab.docsearch.utils.Messages;
import org.jab.docsearch.utils.MetaReport;
import org.jab.docsearch.utils.NoticeLevel;
import org.jab.docsearch.utils.SimpleBookmark;
import org.jab.docsearch.utils.Table;
import org.jab.docsearch.utils.UnZippHandler;
import org.jab.docsearch.utils.Utils;
import org.jab.docsearch.utils.ZippHandler;
import org.jab.docsearch.utils.docTypeHandler;

/**
 * This is main DocSearcher class that extends JFrame. It implements a web
 * browser like interface to a tailored Lucene search index.
 * 
 * @see DocSearcherIndex DocSearcherIndex
 * @version $Id: DocSearch.java,v 1.26 2006/06/26 20:28:21 henschel Exp $
 */
public final class DocSearch extends JFrame implements ActionListener {
    /**
     * Log4J
     */
    private Logger logger = null;
    /**
     * Environment
     */
    private Environment env = Environment.getInstance();
    /**
     * FileEnvironment
     */
    private FileEnvironment fEnv = FileEnvironment.getInstance();
    private boolean isWorking = false;
    private String USER_NAME = System.getProperty("user.name");
    private String cdRomDefaultHome = FileUtils.addFolder(System.getProperty("user.dir"), "cdrom_indexes");
    private String cdRomIdxList = FileUtils.addFolder(cdRomDefaultHome, "cdrom_indexes_list.htm");
    private  String cdRomIdxDir = FileUtils.addFolder(cdRomDefaultHome, "indexes");
    // TODO move tempDir to FileEnvironment 
    public String tempDir = System.getProperty("java.io.tmpdir");
    //private  String cdRomTempIdxDir = FileUtils.addFolder(tempDir, "indexes");
    public String lafChosen = "";
    //
    private boolean isCDSearchTool = isThisOnACd(cdRomDefaultHome);
    private boolean currentlySearching = false;
    //
    public String gateway = "";
    public String gatewayPwd = "";
    public String gatewayUser = "";
    public String emailFormat = "text";
    public String sendEmailNotice = "";
    public ArrayList adminEmails = new ArrayList();
    //
    public ArrayList handlerList = new ArrayList();
    private final static String[] searchOpts = { Messages.getString("DocSearch.titleAndDocBody"), Messages.getString("DocSearch.titleText"), Messages.getString("DocSearch.summaryText"), Messages.getString("DocSearch.bodyText"), Messages.getString("DocSearch.keywordsText") };
    private final static String[] fileTypesToFind = { Messages.getString("DocSearch.Web_Pages"), Messages.getString("DocSearch.Open/Star_Office_Files"), Messages.getString("DocSearch.MS_Office_Files"), Messages.getString("DocSearch.RTF_Files"), Messages.getString("DocSearch.PDF_Files"), Messages.getString("DocSearch.TEXT_Files"), Messages.getString("DocSearch.java_source_code") };
    private final static String[] fileTypesToGet = { "htm", "sxc sxd sxi sxp sxw", "doc xls", "rtf", "pdf", "txt", "java" };
    private final static String fileString = "file:///";
    private final static String pathSep = FileUtils.PATH_SEPARATOR;
    public final static GenericFilter wf = new GenericFilter();
    public final static FolderFilter ff = new FolderFilter();

    // printing vars
    private static final int kDefaultX = 740;
    private static final int kDefaultY = 480;
    // private static final int prefScale = 0;

    //
    private String htmlTag;
    private String wordTag;
    private String excelTag;
    private String pdfTag;
    private String textTag;
    private String rtfTag;
    private String ooImpressTag;
    private String ooWriterTag;
    private String ooCalcTag;
    private String ooDrawTag;
    private String openDocumentTextTag;
    private boolean loadExternal = false;
    private String defaultSaveFolder = "";
    private String lastSearchedText = "";
    private String blankFile = "";
    private String lastSearch = Messages.getString("DocSearch.lastSearch");
    private boolean hasErr = false;
    private boolean isLoading = true;
    private boolean hasIcons = true;
    private String errString = Messages.getString("DocSearch.unknownError");

    // TODO move this files to FileEnvironment or remove this variables if not used (oo after rewrite parsing)
    public String rtfTextFile = FileUtils.addFolder(tempDir, "temp_rtf_file_" + USER_NAME + ".txt");
    public String pdfTextFile = FileUtils.addFolder(tempDir, "temp_pdf_file_" + USER_NAME + ".txt");
    public String htmlTextFile = FileUtils.addFolder(tempDir, "temp_html_file_" + USER_NAME + ".txt");
    public String ooTextFile = FileUtils.addFolder(tempDir, "temp_oo_file_" + USER_NAME + ".xml");
    public String ooMetaTextFile = FileUtils.addFolder(tempDir, "temp_oo_meta_file_" + USER_NAME + ".xml");
    public String ooTextOnlyFile = FileUtils.addFolder(tempDir, "temp_oo_text_file_" + USER_NAME + ".txt");

    // GUI items
    private String curStatusString = Messages.getString("DocSearch.loading");
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenu reportsMenu;
    private JMenu helpMenu;
    private JMenu bookMarkMenu;
    private JMenu toolsMenu;
    private JMenu indexMenu;
    private JOptionPane pane;
    private JMenuItem mi;
    private JComboBox searchField;
    private JLabel searchLabel;
    private String dsDoSearch = Messages.getString("DocSearch.doSearch");
    private JButton searchButton;
    private JPanel[] panels;
    private int numPanels = 1;
    private Searcher searcher;
    private Hits hits;
    private Query query;
    private Hyperactive hl = new Hyperactive();
    private String[] colors;
    private JScrollPane scrollPane;
    private JEditorPane editorPane;
    private JToolBar toolbar;
    private JButton[] iconButtons;
    private boolean hasStartPage = false;
    private String startPageString;
    private String helpPageString;
    private JComponentVista vista;
    private JMenu prefMenu = new JMenu(Messages.getString("DocSearch.printPreferences"), true);
    private JRadioButtonMenuItem scale2RadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scale2X"));
    private JRadioButtonMenuItem scaleFitRadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scaleToFit"));
    private JRadioButtonMenuItem scaleHalfRadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scaleHalf"));
    private JRadioButtonMenuItem scaleOffRadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scaleOff"), true);
    private JRadioButtonMenuItem scaleXRadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scaleWidth"));
    private JRadioButtonMenuItem scaleYRadioBut = new JRadioButtonMenuItem(Messages.getString("DocSearch.scaleLength"));

    private String dsKwds = Messages.getString("DocSearch.keywords");

    private PrintMIListener pml = new PrintMIListener();
    private JRadioButton keywords;
    private JRadioButton phrase;
    private JLabel searchInLabel;
    private JLabel searchTypeLabel;
    private JComboBox searchIn;
    private JPanel sizeAndTypePanel;
    private JPanel fileTypePanel;
    private JCheckBox useType;
    private JComboBox fileType;
    private JLabel fileTypeLabel;
    private JPanel sizePanel;
    private JCheckBox useSize;
    private JLabel sizeFromLabel;
    private JLabel sizeToLabel;
    private JTextField sizeToField;
    private JTextField sizeFromField;
    private ProgressPanel pPanel;
    private ButtonGroup bg;
    private LinkedList backList = new LinkedList();
    private LinkedList forwardList = new LinkedList();
    private long maxFileSizeInt = 1000000;
    private int forwardPos = -1;
    private int backwardPos = -1;
    private String dsHome = Messages.getString("DocSearch.home");
    private String dsHomeTip = Messages.getString("DocSearch.homeTip");
    public String curPage = dsHome; // home always means the last searchresults
    private ArrayList indexes = new ArrayList();
    private ArrayList bookmarksList = new ArrayList();
    private JLabel dirLabel = new JLabel(Messages.getString("DocSearch.statusUp"));

    // GUI items for advanced searching
    private JPanel metaPanel;
    private JPanel datePanel;
    private JCheckBox useDate;
    private JTextField fromField;
    private JLabel fromLabel;
    private JLabel toLabel;
    private JTextField toField;
    private CheckBoxListener cbl;
    private JPanel authorPanel;
    private JCheckBox useAuthor;
    private JTextField authorField;
    private JLabel authorLabel;
    private JTabbedPane tabbedPane;
    private int maxNumHitsShown = 250;

    public Index idx;

    // STRING CONSTANTS
    public static final String CREATE_SEARCHABLE_CD = Messages.getString("DocSearch.makeCD");
    public static final String TOOLS = Messages.getString("DocSearch.tools");
    public static final String EML_SUBJ = Messages.getString("DocSearch.emailSubject");
    public static final String FROM_ADDR = Messages.getString("DocSearch.fromAddr");
    public static final String dsDoHndler = Messages.getString("DocSearch.doHndlr");
    public static final String dsNotIdxdMeta = Messages.getString("DocSearch.nonMetaSpiders");
    public static final String dsKeywordTip = Messages.getString("DocSearch.keywordsTip");
    public static final String dsPhraseTip = Messages.getString("DocSearch.phraseTip");
    public static final String dsOpen = Messages.getString("DocSearch.open");
    public static final String ERROR_CREATING_FOLDER = Messages.getString("DocSearch.errCreatingFold");
    public static final String dsOpenTip = Messages.getString("DocSearch.openTip");
    public static final String dsTitleAndDocBody = Messages.getString("DocSearch.titleAndDocBody");
    public static final String dsTitle = Messages.getString("DocSearch.title");
    public static final String dsSummary = Messages.getString("DocSearch.summary");
    public static final String dsDocBody = Messages.getString("DocSearch.docBody");
    public static final String dsSave = Messages.getString("DocSearch.dsSave");
    public static final String dsSavePageTip = Messages.getString("DocSearch.dsSavePageTip");
    public static final String dsOpenInBrowse = Messages.getString("DocSearch.openInBrowser");
    public static final String dsOpenInBrowseTip = Messages.getString("DocSearch.openInBrowseTip");
    public static final String dsBack = Messages.getString("DocSearch.back");
    public static final String dsBackTip = Messages.getString("DocSearch.backTip");
    public static final String DO_CD_QUEST = Messages.getString("DocSearch.doCdBld");
    public static final String dsFwd = Messages.getString("DocSearch.fwd");
    public static final String dsFwdTip = Messages.getString("DocSearch.fwdTip");
    public static final String dsRefresh = Messages.getString("DocSearch.refresh");
    public static final String dsRefreshTip = Messages.getString("DocSearch.refreshTip");
    public static final String dsResults = Messages.getString("DocSearch.results");
    public static final String STOP = Messages.getString("DocSearch.stop");
    public static final String dsResultsTip = Messages.getString("DocSearch.resultsTip");
    public static final String dsBookmark = Messages.getString("DocSearch.bookmark");
    public static final String dsBookmarkTip = Messages.getString("DocSearch.bookmarkTip");
    public static final String dsPrint = Messages.getString("DocSearch.print");
    public static final String dsPrintTip = Messages.getString("DocSearch.printTip");
    public static final String dsExit = Messages.getString("DocSearch.exit");
    public static final String dsExitTip = Messages.getString("DocSearch.exitTip");
    public static final String SEARCH_COMPLETE = Messages.getString("DocSearch.searchComp");
    public static final String dsSearchTips = Messages.getString("DocSearch.searchSuggestions");
    public static final String FINISHED_COPYING = Messages.getString("DocSearch.finishedCopying");
    public static final String dsHelp = Messages.getString("DocSearch.help");
    public static final String dsAbout = Messages.getString("DocSearch.about");
    public static final String dsReports = Messages.getString("DocSearch.reports");
    public static final String dsDoMetaReport = Messages.getString("DocSearch.doMetaReport");
    public static final String dsDoServletLogReport = Messages.getString("DocSearch.doServletLogReport");
    public static final String dsDoNewIndex = Messages.getString("DocSearch.doNewIndex");
    public static final String dsDoManageIndex = Messages.getString("DocSearch.doManageIndex");
    public static final String dsReIndex = Messages.getString("DocSearch.reIndex");
    public static final String dsImportIndex = Messages.getString("DocSearch.importIndex");
    public static final String dsIndex = Messages.getString("DocSearch.index");
    public static final String dsBookmarks = Messages.getString("DocSearch.bookmarks");
    public static final String dsCkgFoUpdtsToDoc = Messages.getString("DocSearch.ckgFoUpdts");
    public static final String dsClearBookmarks = Messages.getString("DocSearch.clearBookmarks");
    public static final String dsAddBookmark = Messages.getString("DocSearch.addBookmark");
    public static final String errLoadPage = Messages.getString("DocSearch.errorLoadingPage");
    public static final String errReported = Messages.getString("DocSearch.errorReported");
    public static final String loadingP = Messages.getString("DocSearch.loadingPage");
    public static final String cmdUsage = Messages.getString("DocSearch.cmdUsage");
    public static final String plsWait = Messages.getString("DocSearch.plsWait");
    public static final String dsFileTooBig = Messages.getString("DocSearch.skippingFileTooBig");
    public static final String waitForIndexUpDate = Messages.getString("DocSearch.idxUpdating");
    public static final String ckFoUpdaTo = Messages.getString("DocSearch.ckForUpdatesTo");
    public static final String updComp = Messages.getString("DocSearch.upDaComp");
    public static final String dsTpx = Messages.getString("DocSearch.topics");
    public static final String dsErrPrint = Messages.getString("DocSearch.errPrinting");
    public static final String dsErrIdxg = Messages.getString("DocSearch.errIdxg");
    public static final String dsErrObtSi = Messages.getString("DocSearch.errObtSize");
    public static final String dsErr = Messages.getString("DocSearch.err");
    public static final String dsSchin = Messages.getString("DocSearch.Searching");
    public static final String dsUpdts = Messages.getString("DocSearch.updates");
    public static final String idxFldr = Messages.getString("DocSearch.idxFldr");
    public static final String dsExists = Messages.getString("DocSearch.exists");
    public static final String dsErrLower = Messages.getString("DocSearch.errLowerCase");
    public static final String dsFSE = Messages.getString("DocSearch.errFilSave");
    public static final String dsWasSaved = Messages.getString("DocSearch.wasSaved");
    public static final String dsNone = Messages.getString("DocSearch.none");
    public static final String dsRsltsFoSch = Messages.getString("DocSearch.rsltsForSrch");
    public static final String dsErrParseNums = Messages.getString("DocSearch.errParseNumFs");
    public static final String dsSrchStr = Messages.getString("DocSearch.srchStr");
    public static final String dsDocsFndInIndx = Messages.getString("DocSearch.docFndInIndx");
    public static final String dsNumNewFiles = Messages.getString("DocSearch.newFiles");
    public static final String dsNumDelFiles = Messages.getString("DocSearch.deletedFiles");
    public static final String dsNumUnchangedFiles = Messages.getString("DocSearch.unchangedFiles");
    public static final String dsNumchangedFiles = Messages.getString("DocSearch.changedFiles");
    public static final String dsDox = Messages.getString("DocSearch.dox");
    public static final String dsMxNumHits = Messages.getString("DocSearch.maxNumHits");
    public static final String dsExceeded = Messages.getString("DocSearch.exceeded");
    public static final String dsUnk = Messages.getString("DocSearch.unk");
    public static final String dsFailIdxDocs = Messages.getString("DocSearch.fldUpdates");
    public static final String dsTtlDxInIdx = Messages.getString("DocSearch.ttlDox");
    public static final String dsErrParseScore = Messages.getString("DocSearch.errParseScore");
    public static final String dsWasNotSearched = Messages.getString("DocSearch.wns");
    public static final String dsOpt = Messages.getString("DocSearch.dsOpt");
    public static final String dsTotalDocsFndIndx = Messages.getString("DocSearch.tdfi");
    public static final String dsTotHits = Messages.getString("DocSearch.totHits");
    public static final String dsErrPrfSrch = Messages.getString("DocSearch.errPerfSrch");
    public static final String dsCrptdIdx = Messages.getString("DocSearch.crptdIdx");
    public static final String dsMkIdx = Messages.getString("DocSearch.makeIdx");
    public static final String FOLDER_ALREADY_EXISTS = Messages.getString("DocSearch.foldAlreadyMade");
    public static final String dsErrLdgFi = Messages.getString("DocSearch.errLdgFi");
    public static final String dsErrSetPa = Messages.getString("DocSearch.errSetPa");
    public static final String dsErrLdgPa = Messages.getString("DocSearch.errLdgPa");
    public static final String PROVIDE_TEXT = Messages.getString("DocSearch.errNoText");
    public static final String dsErrSaFi = Messages.getString("DocSearch.errSaveFi");
    public static final String dsIdxg = Messages.getString("DocSearch.idxg");
    public static final String dsLdg = Messages.getString("DocSearch.ldg");
    public static final String dsLoaded = Messages.getString("DocSearch.loaded");
    public static final String dsDaysOld = Messages.getString("DocSearch.daysOld");
    public static final String dsNotExist = Messages.getString("DocSearch.errDoesntExist");
    public static final String dsErrIdxgFi = Messages.getString("DocSearch.errIdxng");
    public static final String dsMetaFiles = Messages.getString("DocSearch.metaF");
    public static final String dsFndFldr = Messages.getString("DocSearch.foundFldr");
    public static final String dsIdxCrtd = Messages.getString("DocSearch.idxCreated");
    public static final String dsIdxsRblt = Messages.getString("DocSearch.idxsReblt");
    public static final String dsBknLink = Messages.getString("DocSearch.bknLink");
    public static final String lnkNoChanges = Messages.getString("DocSearch.nonCHangedLink");
    public static final String dsReIdxgLnk = Messages.getString("DocSearch.reIdxgLnk");
    public static final String dsSpdrUpdteComp = Messages.getString("DocSearch.dsSpiderUpdtComp");
    public static final String dsLkngFoLnx = Messages.getString("DocSearch.lookingForLinks");
    public static final String dsSpiderNewUrl = Messages.getString("DocSearch.dsSpiderNewUrl");
    public static final String dsRmvgIdxFis = Messages.getString("DocSearch.rmvgIdxFis");
    public static final String dsDeleting = Messages.getString("DocSearch.deleting");
    public static final String CREATE_NEW_SPIDER_IDX = Messages.getString("DocSearch.createSpideredIdx");
    public static final String dsIdxRemoved = Messages.getString("DocSearch.idxRemoved");
    public static final String dsUnZipn = Messages.getString("DocSearch.unzippn");
    public static final String dsUnZipD = Messages.getString("DocSearch.unzipd");
    public static final String dsUpdtArchTbl = Messages.getString("DocSearch.updtgArchTbl");
    public static final String dsArchTblUpdtd = Messages.getString("DocSearch.archTblUpdtd");
    public static final String dsPcntDnld = Messages.getString("DocSearch.pcntDnld");
    public static final String dsOfFile = Messages.getString("DocSearch.ofFile");
    public static final String dsBytsTot = Messages.getString("DocSearch.totalBytes");
    public static final String dsDnLdErr = Messages.getString("DocSearch.errDnLd");
    public static final String dsImptg = Messages.getString("DocSearch.importing");
    public static final String dsImprtDn = Messages.getString("DocSearch.imprtDone");
    public static final String dsImprtSuccess = Messages.getString("DocSearch.imprtSuccess");
    public static final String dsWasImprtd = Messages.getString("DocSearch.wasImprtd");
    public static final String dsErrImptg = Messages.getString("DocSearch.errImprtg");
    public static final String dsArchDescFnd = Messages.getString("DocSearch.archDescFnd");
    public static final String dsErrParseMnfst = Messages.getString("DocSearch.errParseMnfst");
    public static final String COPY_FILE = Messages.getString("DocSearch.copyFile");
    public static final String COPYING_FILE = Messages.getString("DocSearch.copyingFile");
    private String defaultHndlr = "";


    /**
     * Method main: start method
     *
     * @param args
     */
    public static void main(String[] args) {

        // init logging
        Logging logging = new Logging();
        logging.init();

        Logger mainLogger = Logger.getLogger(DocSearch.class.getName());

        // parse params
        boolean hasCommands = false;
        String commandString = null;
        String indexString = null;
        boolean enableLogfile = false;

        for (int i = 0; i < args.length; i++) {
            String arg = args[i];

            if (arg.startsWith("enable_logfile")) {
                enableLogfile = true;
            } else {
                if (commandString == null) {
                    hasCommands = true;
                    commandString = arg;
                }
                else {
                    indexString = arg;
                }
            }
        }

        // add logfile logger if enable_logfile option as startargument
        if (enableLogfile) {
            logging.addFileLogger();
        }

        // Environment
        Environment env = Environment.getInstance();
        // FileEnvironment
        FileEnvironment fEnv = FileEnvironment.getInstance();

        // set look and feel
        try {
            UIManager.setLookAndFeel("de.muntjak.tinylookandfeel.TinyLookAndFeel");
        }
        catch (Exception e) {
            mainLogger.error("main() Unable to load TINYLAF jar resources.", e);
        }
        
        // splash
        DocSplashViewer splash = new DocSplashViewer("splash.gif", "DocSearcher " + Messages.getString("DocSearch.version") + " " + Messages.getString("DocSearch.loading"));
        if (! hasCommands) {
            splash.display();
        }

        // gets OS type
        env.setOSType(Utils.getOSType());

        // gets GUI mode
        if (hasCommands) {
            env.setGUIMode(false);
        }
        else {
            env.setGUIMode(true);
        }

        // gets CDROM dir
        env.setCDROMDir(Utils.getCDROMDir(env.getOSType()));

        // users home
        fEnv.setUserHome(Utils.getUserHome(env.getOSType(), System.getProperty("user.home")));
        
        final DocSearch sw = new DocSearch();
        splash.setMonitor(sw);

        sw.init();

        splash.close();

        if (! hasCommands) {
            sw.setVisible(true);
            sw.checkUpdates();
        }
        else {
            if (commandString.equals(Messages.getString("DocSearch.updateCMD")) && indexString == null) {
                sw.checkUpdates();
                System.exit(0);
            }
            else {
                sw.doCommand(commandString, indexString);
            }
        }
    }
    

    /**
     * Constructor
     */
    public DocSearch() {
        super(Messages.getString("DocSearch.appTitle"));

        // get logger
        logger = Logger.getLogger(getClass().getName());

        //
        File testCDFi = new File(cdRomDefaultHome);
        Properties sys = new Properties(System.getProperties());
        if (testCDFi.exists()) {
            sys.setProperty("disableLuceneLocks", "true");
            logger.info("DocSearch() " + Messages.getString("DocSearch.disableLocks"));
        }
        else {
            sys.setProperty("disableLuceneLocks", "false");
        }
        //
        checkCDROMDir();
        defaultHndlr = getBrowserFile();
        loadSettings();
        //
        String iconDir = fEnv.getIconDirectory();
        //
        pPanel = new ProgressPanel("", 100L);
        pPanel.init();
        phrase = new JRadioButton(Messages.getString("DocSearch.phrase"));
        searchField = new JComboBox();
        searchField.addActionListener(new ComboListener());
        searchIn = new JComboBox(searchOpts);
        searchTypeLabel = new JLabel(Messages.getString("DocSearch.searchType"));
        searchInLabel = new JLabel(Messages.getString("DocSearch.searchIn"));
        keywords = new JRadioButton(dsKwds);
        //
        searchLabel = new JLabel(Messages.getString("DocSearch.searchFor"));
        searchButton = new JButton(dsDoSearch);
        // TODO alt text to resource
        htmlTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.HTML_ICON) + "\" border=\"0\" alt=\"Web Page Document\">";
        wordTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.MS_WORD_ICON) + "\" border=\"0\" alt=\"MS Word Document\">";
        excelTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.MS_EXCEL_ICON) + "\" border=\"0\" alt=\"MS Excel Document\">";
        pdfTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.PDF_ICON) + "\" border=\"0\" alt=\"PDF Document\">";
        textTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.TEXT_ICON) + "\" border=\"0\" alt=\"Text Document\">";
        rtfTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.RTF_ICON) + "\" border=\"0\" alt=\"RTF Document\">";
        ooImpressTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.OO_IMPRESS_ICON) + "\" border=\"0\" alt=\"OpenOffice Impress Document\">";
        ooWriterTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.OO_WRITER_ICON) + "\" border=\"0\" alt=\"OpenOffice Writer Document\">";
        ooCalcTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.OO_CALC_ICON) + "\" border=\"0\" alt=\"OpenOffice Calc Document\">";
        ooDrawTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.OO_DRAW_ICON) + "\" border=\"0\" alt=\"OpenOffice Draw Document\">";
        openDocumentTextTag = "<img src=\"" + fileString + FileUtils.addFolder(iconDir, FileType.OPENDOCUMENT_TEXT_ICON) + "\" border=\"0\" alt=\"OpenDocument Text Document\">";
        //
        idx = new Index(this);
        colors = new String[2];
        colors[0] = "ffeffa";
        colors[1] = "fdffda";
        startPageString = FileUtils.addFolder(fEnv.getStartDirectory(), FileEnvironment.FILENAME_START_PAGE);
        helpPageString = FileUtils.addFolder(fEnv.getStartDirectory(), FileEnvironment.FILENAME_HELP_PAGE);
        File startPageFile = new File(startPageString);
        if (startPageFile.exists()) {
            logger.debug("DocSearch() Start Page is: " + startPageString);
            hasStartPage = true;
        }
        else {
            logger.error("DocSearch() Start Page NOT FOUND where expected: " + startPageString);
        }
        defaultSaveFolder = FileUtils.addFolder(fEnv.getWorkingDirectory(), "saved_searches");
        iconDir = FileUtils.addFolder(fEnv.getStartDirectory(), "icons");
        File iconFolder = new File(iconDir);
        searchField.setEditable(true);
        searchField.addItem("");

        bg = new ButtonGroup();
        bg.add(phrase);
        bg.add(keywords);
        keywords.setSelected(true);

        keywords.setToolTipText(dsKeywordTip);
        phrase.setToolTipText(dsPhraseTip);

        int iconInt = 2;
        searchIn.setSelectedIndex(3);
        searchField.setPreferredSize(new Dimension(370, 22));

        if (iconFolder.exists()) {
            int numIcons = 12;
            toolbar = new JToolBar();
            iconButtons = new JButton[numIcons];

            iconButtons[0] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "fileopen.png")));
            iconButtons[0].setToolTipText(dsOpenTip);
            iconButtons[0].setActionCommand(dsOpen);
            iconButtons[0].addActionListener(this);
            iconButtons[0].setMnemonic(KeyEvent.VK_O);

            iconButtons[1] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "filesave.png")));
            iconButtons[1].setToolTipText(dsSavePageTip);
            iconButtons[1].setActionCommand(dsSave);
            iconButtons[1].addActionListener(this);
            iconButtons[1].setMnemonic(KeyEvent.VK_S);

            iconButtons[2] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "html.png")));
            iconButtons[2].setToolTipText(dsOpenInBrowseTip);
            iconButtons[2].setActionCommand(dsOpenInBrowse);
            iconButtons[2].addActionListener(this);
            iconButtons[2].setMnemonic(KeyEvent.VK_E);

            iconButtons[3] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "back.png")));
            iconButtons[3].setToolTipText(dsBackTip);
            iconButtons[3].setActionCommand(dsBack);
            iconButtons[3].addActionListener(this);
            iconButtons[3].setMnemonic(KeyEvent.VK_B);

            iconButtons[4] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "home.png")));
            iconButtons[4].setToolTipText(dsHome);
            iconButtons[4].setActionCommand(dsHomeTip);
            iconButtons[4].addActionListener(this);
            iconButtons[4].setMnemonic(KeyEvent.VK_H);

            iconButtons[5] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "forward.png")));
            iconButtons[5].setToolTipText(dsFwdTip);
            iconButtons[5].setActionCommand(dsFwd);
            iconButtons[5].addActionListener(this);
            iconButtons[5].setMnemonic(KeyEvent.VK_F);

            iconButtons[6] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "refresh.png")));
            iconButtons[6].setToolTipText(dsRefreshTip);
            iconButtons[6].setActionCommand(dsRefresh);
            iconButtons[6].addActionListener(this);
            iconButtons[6].setMnemonic(KeyEvent.VK_L);

            iconButtons[7] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "search_results.gif")));
            iconButtons[7].setToolTipText(dsResultsTip);
            iconButtons[7].setActionCommand(dsResults);
            iconButtons[7].addActionListener(this);
            iconButtons[7].setMnemonic(KeyEvent.VK_R);

            iconButtons[8] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "bookmark.png")));
            iconButtons[8].setToolTipText(dsBookmarkTip);
            iconButtons[8].setActionCommand(dsBookmark);
            iconButtons[8].addActionListener(this);
            iconButtons[8].setMnemonic(KeyEvent.VK_M);

            iconButtons[9] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "fileprint.png")));
            iconButtons[9].setToolTipText(dsPrintTip);
            iconButtons[9].setActionCommand(dsPrint);
            iconButtons[9].addActionListener(pml);
            iconButtons[9].setMnemonic(KeyEvent.VK_P);

            iconButtons[10] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "configure.png")));
            iconButtons[10].setToolTipText(dsOpt);
            iconButtons[10].setActionCommand(dsOpt);
            iconButtons[10].addActionListener(this);
            iconButtons[10].setMnemonic(KeyEvent.VK_HOME);

            iconButtons[numIcons - 1] = new JButton(new ImageIcon(FileUtils.addFolder(iconDir, "stop.png")));
            iconButtons[numIcons - 1].setToolTipText(STOP);
            iconButtons[numIcons - 1].setActionCommand(STOP);
            iconButtons[numIcons - 1].addActionListener(this);
            iconButtons[numIcons - 1].setMnemonic(KeyEvent.VK_X);

            for (int i = 0; i < numIcons; i++) {
                // add the icons to the toolbar
                toolbar.add(iconButtons[i]);
                if ((i == 1) || (i == 2) || (i == 5) || (i >= 7)) {
                    toolbar.addSeparator();
                }

                toolbar.setFloatable(false);
            }

            iconButtons[5].setEnabled(false); // forward
            iconButtons[3].setEnabled(false); // back

            Image iconImage = Toolkit.getDefaultToolkit().getImage(FileUtils.addFolder(iconDir, "ds.gif"));
            this.setIconImage(iconImage);
        } else {
            hasIcons = false;
            iconInt = 1;
        }

        menuBar = new JMenuBar();
        fileMenu = new JMenu(Messages.getString("DocSearch.File"));

        // print gui items
        JMenuItem printMI = new JMenuItem(dsPrint);
        printMI.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P, Event.CTRL_MASK));
        scale2RadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, Event.CTRL_MASK));
        scaleFitRadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F, Event.CTRL_MASK));
        scaleHalfRadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_H, Event.CTRL_MASK));
        scaleOffRadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, Event.CTRL_MASK));
        scaleXRadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, Event.CTRL_MASK));
        scaleYRadioBut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_L, Event.CTRL_MASK));
        printMI.addActionListener(pml);

        scaleXRadioBut.addActionListener(new ScaleXListener());
        scaleYRadioBut.addActionListener(new ScaleYListener());
        scaleFitRadioBut.addActionListener(new ScaleFitListener());
        scaleHalfRadioBut.addActionListener(new ScaleHalfListener());
        scale2RadioBut.addActionListener(new Scale2Listener());

        ButtonGroup scaleSetGroup = new ButtonGroup();
        scaleSetGroup.add(scale2RadioBut);
        scaleSetGroup.add(scaleFitRadioBut);
        scaleSetGroup.add(scaleHalfRadioBut);
        scaleSetGroup.add(scaleOffRadioBut);
        scaleSetGroup.add(scaleXRadioBut);
        scaleSetGroup.add(scaleYRadioBut);
        prefMenu.add(scaleXRadioBut);
        prefMenu.add(scaleYRadioBut);
        prefMenu.add(scaleFitRadioBut);
        prefMenu.add(scaleHalfRadioBut);
        prefMenu.add(scale2RadioBut);
        prefMenu.addSeparator();
        prefMenu.add(scaleOffRadioBut);
        fileMenu.add(prefMenu);
        fileMenu.add(printMI);
        //
        bookMarkMenu = new JMenu(dsBookmarks);
        mi = new JMenuItem(dsAddBookmark);
        mi.addActionListener(this);
        bookMarkMenu.add(mi);
        //
        toolsMenu = new JMenu(TOOLS);
        mi = new JMenuItem(CREATE_SEARCHABLE_CD);
        mi.addActionListener(this);
        toolsMenu.add(mi);
        toolsMenu.addSeparator();
        mi = new JMenuItem(dsOpt);
        mi.addActionListener(this);
        toolsMenu.add(mi);
        //
        mi = new JMenuItem(dsClearBookmarks);
        mi.addActionListener(this);
        bookMarkMenu.add(mi);

        bookMarkMenu.addSeparator();

        // add and loaded bookmarks
        indexMenu = new JMenu(dsIndex);
        mi = new JMenuItem(dsDoNewIndex);
        mi.addActionListener(this);
        indexMenu.add(mi);
        //
        mi = new JMenuItem(CREATE_NEW_SPIDER_IDX);
        mi.addActionListener(this);
        indexMenu.add(mi);
        //
        mi = new JMenuItem(dsDoManageIndex);
        mi.addActionListener(this);
        indexMenu.add(mi);

        mi = new JMenuItem(dsReIndex);
        mi.addActionListener(this);
        indexMenu.add(mi);

        indexMenu.addSeparator();
        mi = new JMenuItem(dsImportIndex);
        mi.addActionListener(this);
        indexMenu.add(mi);

        fileMenu.addSeparator();
        mi = new JMenuItem(dsExit);
        mi.addActionListener(this);
        fileMenu.add(mi);

        helpMenu = new JMenu(dsHelp);
        mi = new JMenuItem(dsSearchTips);
        mi.addActionListener(this);
        helpMenu.add(mi);
        mi = new JMenuItem(dsAbout);
        mi.addActionListener(this);
        helpMenu.add(mi);
        // dsTpx
        mi = new JMenuItem(dsTpx);
        mi.addActionListener(this);
        helpMenu.add(mi);
        //
        reportsMenu = new JMenu(dsReports);
        mi = new JMenuItem(dsDoMetaReport);
        mi.addActionListener(this);
        reportsMenu.add(mi);
        mi = new JMenuItem(dsDoServletLogReport);
        mi.addActionListener(this);
        reportsMenu.add(mi);
        menuBar.add(fileMenu);
        menuBar.add(indexMenu);
        menuBar.add(bookMarkMenu);
        menuBar.add(reportsMenu);
        menuBar.add(toolsMenu);
        menuBar.add(helpMenu);
        setJMenuBar(menuBar);

        editorPane = new JEditorPane("text/html", lastSearch);
        editorPane.setEditable(false);
        editorPane.addHyperlinkListener(hl);
        if (hasStartPage) {
            try {
                editorPane.setContentType("text/html");
                if (setPage("home")) {
                    logger.info("DocSearch() loaded start page: " + startPageString);
                }
            }
            catch (Exception e) {
                editorPane.setText(lastSearch);
            }
        } else {
            logger.warn("DocSearch() no start page loaded");
        }

        scrollPane = new JScrollPane(editorPane);
        scrollPane.setPreferredSize(new Dimension(1024, 720));
        scrollPane.setMinimumSize(new Dimension(900, 670));
        scrollPane.setMaximumSize(new Dimension(1980, 1980));

        // create panels
        // add printing stuff
        vista = new JComponentVista(editorPane, new PageFormat());

        JPanel topPanel = new JPanel();
        JPanel bottomPanel = new JPanel();
        topPanel.add(searchLabel);
        topPanel.add(searchField);
        topPanel.add(searchButton);
        bottomPanel.add(searchTypeLabel);
        bottomPanel.add(keywords);
        bottomPanel.add(phrase);
        bottomPanel.add(searchInLabel);
        bottomPanel.add(searchIn);

        searchButton.setMnemonic(KeyEvent.VK_A);

        // GUI items for advanced searching
        metaPanel = new JPanel();
        datePanel = new JPanel();
        useDate = new JCheckBox(Messages.getString("DocSearch.useDateProps"));
        fromField = new JTextField(11);
        fromLabel = new JLabel(Messages.getString("DocSearch.from"));
        toLabel = new JLabel(Messages.getString("DocSearch.to"));
        toField = new JTextField(11);
        cbl = new CheckBoxListener();
        authorPanel = new JPanel();
        useAuthor = new JCheckBox(Messages.getString("DocSearch.useAuthProps"));
        authorField = new JTextField(31);
        authorLabel = new JLabel(Messages.getString("DocSearch.author"));
        tabbedPane = new JTabbedPane();
        authorPanel.add(useAuthor);
        authorPanel.add(authorLabel);
        authorPanel.add(authorField);

        // combine stuff
        datePanel.add(useDate);
        datePanel.add(fromLabel);
        datePanel.add(fromField);
        datePanel.add(toLabel);
        datePanel.add(toField);

        metaPanel.setLayout(new BorderLayout());
        metaPanel.setBorder(new TitledBorder(Messages.getString("DocSearch.dateAndAuthor")));
        metaPanel.add(datePanel, BorderLayout.NORTH);
        metaPanel.add(authorPanel, BorderLayout.SOUTH);

        useDate.addActionListener(cbl);
        useAuthor.addActionListener(cbl);

        fromField.setText(DateTimeUtils.getLastYear());
        toField.setText(DateTimeUtils.getToday());
        authorField.setText(System.getProperty("user.name"));

        panels = new JPanel[numPanels];
        for (int i = 0; i < numPanels; i++) {
            panels[i] = new JPanel();
        }

        // add giu to panels
        panels[0].setLayout(new BorderLayout());
        panels[0].add(topPanel, BorderLayout.NORTH);
        panels[0].add(bottomPanel, BorderLayout.SOUTH);
        panels[0].setBorder(new TitledBorder(Messages.getString("DocSearch.searchCritera")));
        searchButton.addActionListener(this);

        sizeAndTypePanel = new JPanel();
        fileTypePanel = new JPanel();
        useType = new JCheckBox(Messages.getString("DocSearch.useFileCritera"));
        useType.addActionListener(cbl);
        fileType = new JComboBox(fileTypesToFind);
        fileTypeLabel = new JLabel(Messages.getString("DocSearch.findOnlyTheseFileTypes"));
        fileTypePanel.add(useType);
        fileTypePanel.add(fileTypeLabel);
        fileTypePanel.add(fileType);

        sizePanel = new JPanel();
        useSize = new JCheckBox(Messages.getString("DocSearch.useFileSizeCriteria"));
        useSize.addActionListener(cbl);
        sizeFromLabel = new JLabel(Messages.getString("DocSearch.fromK"));
        sizeToLabel = new JLabel(Messages.getString("DocSearch.toK"));
        sizeFromField = new JTextField(10);
        sizeFromField.setText("0");
        sizeToField = new JTextField(10);
        sizeToField.setText("100");
        sizePanel.add(useSize);
        sizePanel.add(sizeFromLabel);
        sizePanel.add(sizeFromField);
        sizePanel.add(sizeToLabel);
        sizePanel.add(sizeToField);

        sizeAndTypePanel.setLayout(new BorderLayout());
        sizeAndTypePanel.setBorder(new TitledBorder(Messages.getString("DocSearch.typeAndSize")));
        sizeAndTypePanel.add(fileTypePanel, BorderLayout.NORTH);
        sizeAndTypePanel.add(sizePanel, BorderLayout.SOUTH);

        // set up the tabbed pane
        tabbedPane.addTab(Messages.getString("DocSearch.genOpts"), null, panels[0], Messages.getString("DocSearch.genSeCri"));
        tabbedPane.addTab(Messages.getString("DocSearch.dateAndAuthor"), null, metaPanel, Messages.getString("DocSearch.dateAuthProp"));
        tabbedPane.addTab(Messages.getString("DocSearch.typeAndSize"), null, sizeAndTypePanel, Messages.getString("DocSearch.typeAndSizeOpt"));

        // gridbag
        getContentPane().setLayout(new GridLayout(1, numPanels + iconInt + 1));
        GridBagLayout gridbaglayout = new GridBagLayout();
        GridBagConstraints gridbagconstraints = new GridBagConstraints();
        getContentPane().setLayout(gridbaglayout);
        int start = 0;
        if (hasIcons) {
            gridbagconstraints.fill = GridBagConstraints.HORIZONTAL;
            gridbagconstraints.insets = new Insets(1, 1, 1, 1);
            gridbagconstraints.gridx = 0;
            gridbagconstraints.gridy = 0;
            gridbagconstraints.gridwidth = 1;
            gridbagconstraints.gridheight = 1;
            gridbagconstraints.weightx = 1.0D;
            gridbagconstraints.weighty = 0.0D;
            gridbaglayout.setConstraints(toolbar, gridbagconstraints);
            getContentPane().add(toolbar);
            start++;
        }

        for (int i = 0; i < numPanels; i++) {
            if (i == 0) {
                gridbagconstraints.fill = GridBagConstraints.HORIZONTAL;
                gridbagconstraints.insets = new Insets(1, 1, 1, 1);
                gridbagconstraints.gridx = 0;
                gridbagconstraints.gridy = i + start;
                gridbagconstraints.gridwidth = 1;
                gridbagconstraints.gridheight = 1;
                gridbagconstraints.weightx = 1.0D;
                gridbagconstraints.weighty = 0.0D;
                gridbaglayout.setConstraints(tabbedPane, gridbagconstraints);
                getContentPane().add(tabbedPane);
            } else {
                gridbagconstraints.fill = GridBagConstraints.HORIZONTAL;
                gridbagconstraints.insets = new Insets(1, 1, 1, 1);
                gridbagconstraints.gridx = 0;
                gridbagconstraints.gridy = i + start;
                gridbagconstraints.gridwidth = 1;
                gridbagconstraints.gridheight = 1;
                gridbagconstraints.weightx = 1.0D;
                gridbagconstraints.weighty = 0.0D;
                gridbaglayout.setConstraints(panels[i], gridbagconstraints);
                getContentPane().add(panels[i]);
            }
        }

        // now add the results area
        gridbagconstraints.fill = GridBagConstraints.HORIZONTAL;
        gridbagconstraints.insets = new Insets(1, 1, 1, 1);
        gridbagconstraints.gridx = 0;
        gridbagconstraints.gridy = iconInt;
        gridbagconstraints.gridwidth = 1;
        gridbagconstraints.gridheight = 1;
        gridbagconstraints.weightx = 1.0D;
        gridbagconstraints.weighty = 1.0D;
        gridbaglayout.setConstraints(scrollPane, gridbagconstraints);
        getContentPane().add(scrollPane);
        JPanel statusP = new JPanel();
        statusP.setLayout(new BorderLayout());
        statusP.add(dirLabel, BorderLayout.WEST);
        statusP.add(pPanel, BorderLayout.EAST);

        // now add the status label
        gridbagconstraints.fill = GridBagConstraints.HORIZONTAL;
        gridbagconstraints.insets = new Insets(1, 1, 1, 1);
        gridbagconstraints.gridx = 0;
        gridbagconstraints.gridy = numPanels + iconInt;
        gridbagconstraints.gridwidth = 1;
        gridbagconstraints.gridheight = 1;
        gridbagconstraints.weightx = 1.0D;
        gridbagconstraints.weighty = 0.0D;
        gridbaglayout.setConstraints(statusP, gridbagconstraints);
        getContentPane().add(statusP);

        //
        File testArchDir = new File(fEnv.getArchiveDirectory());
        if (! testArchDir.exists()) {
            boolean madeDir = testArchDir.mkdir();
            if (! madeDir) {
                logger.warn("DocSearch() " + Messages.getString("DocSearch.errCreateDir"));
            }
            else {
                logger.info("DocSearch() " + Messages.getString("DocSearch.dirCreated") + fEnv.getArchiveDirectory());
            }
        }
        loadIndexes();
        String handlersFiName;
        if (! isCDSearchTool) {
            handlersFiName = FileUtils.addFolder(fEnv.getWorkingDirectory(), "handlers_list.htm");
        }
        else {
            handlersFiName = handlersFiName = FileUtils.addFolder(cdRomDefaultHome, "handlers_list.htm");
        }
        if (! FileUtils.fileExists(handlersFiName)) {
            logger.warn("DocSearch() handlers file not found at: " + handlersFiName);
            getHandlers();
        }
        else {
            doObjectLoad(0, handlersFiName);
        }
    }


    /**
     * Method init
     */
    private void init() {
        //
        // GUI BUILDING
        // close window item
        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowevent) {
                doExit();
            }
        });

        // center on the screen
        Dimension screenD = Toolkit.getDefaultToolkit().getScreenSize();
        int screenWidth = screenD.width;
        int screenHeight = screenD.height;
        setSize(kDefaultX, kDefaultY);
        int newX = 0;
        int newY = 0;
        if (screenWidth > kDefaultX) {
            newX = (screenWidth - kDefaultX) / 2;
        }

        if (screenHeight > kDefaultY) {
            newY = (screenHeight - kDefaultY) / 2;
        }

        if ((newX != 0) || (newY != 0)) {
            setLocation(newX, newY);
        }

        // now determine if we need to create an index
        if ((!hasIndex()) && (!isCDSearchTool)) {
            curStatusString = Messages.getString("DocSearch.initIndex");
            String contentFolderS = FileUtils.addFolder(fEnv.getStartDirectory(), "content");
            File testCF = new File(contentFolderS);
            if (testCF.exists()) {
                try {
                    DocSearcherIndex di = new DocSearcherIndex(contentFolderS, "default index", true, 20, FileUtils.addFolder(fEnv.getIndexDirectory(), "default"), false, "", "", 0, fEnv.getArchiveDirectory());
                    createNewIndex(di, false);
                } catch (Exception eS) {
                    showMessage(Messages.getString("DocSearch.errCreatingIdx"), eS.toString());
                }
            }
        }

        // HANDLE ERRORS
        isLoading = false;
        if (hasErr) {
            showMessage(Messages.getString("DocSearch.initErr"), errString);
        }

        // set up our fields;
        cb();
        setIsWorking(false);
        listAllProps();
    }


    /**
     * Checks the policy for updating the DocSearcherIndexes and if it is time
     * for updating - starts that process
     */
    private void checkUpdates() {
        int numDis = indexes.size();
        if (numDis > 0) {
            setStatus(plsWait + waitForIndexUpDate);
            Iterator it = indexes.iterator();
            DocSearcherIndex di;
            int curDays = 0;
            while (it.hasNext()) {
                di = (DocSearcherIndex) it.next();
                curDays = DateTimeUtils.getDaysOld(di.getLastIndexed());
                setStatus(ckFoUpdaTo + di.getDescription());
                switch (di.getIndexPolicy()) {
                    case 0: // When I say so
                        break;
                    case 1: // During Startup
                        idx.updateIndex(di);
                        break;
                    case 2: // When Index > 1 Day Old
                        if (curDays > 1)
                            idx.updateIndex(di);
                        break;
                    case 3: // When Index > 5 Days old
                        if (curDays > 5)
                            idx.updateIndex(di);
                        break;
                    case 4: // When Index > 30 Days Old
                        if (curDays > 30)
                            idx.updateIndex(di);
                        break;
                    case 5: // When Index > 60 Days Old
                        if (curDays > 60)
                            idx.updateIndex(di);
                        break;
                    case 6: // When Index > 90 Days Old
                        if (curDays > 90)
                            idx.updateIndex(di);
                        break;
                    case 7: // When Index > 180 Days Old
                        if (curDays > 180)
                            idx.updateIndex(di);
                        break;
                    case 8: // When Index > 365 Days Old
                        if (curDays > 365)
                            idx.updateIndex(di);
                        break;
                    default: // whatever
                        break;
                }
            }
        }
        setStatus(updComp);
    }


    /**
     * Handle's main GUI events
     */
    public void handleEventCommand(String s) {
        try {
            // we run validation in a thread so as not to interfere
            // with repaints of GUI
            if (s.equals(dsExit))
                doExit();
            else if (s.equals(CREATE_SEARCHABLE_CD)) {
                doSearchableCdWiz();
            }
            else if (s.equals(dsOpt)) {
                doHandlers();
            }
            else if (s.equals(CREATE_NEW_SPIDER_IDX)) {
                doNewSpiderIdx();
            }
            else if (s.equals(dsRefresh)) {
                setPage(curPage);
            }
            else if (s.equals(dsDoMetaReport)) {
                doMetaReport();
            }
            else if (s.equals(dsDoServletLogReport)) {
                getSeachLogReport();
            }
            else if (s.equals(dsFwd)) {
                doForward();
            }
            else if (s.equals(dsAbout)) {
                showMessage(dsAbout, Messages.getString("DocSearch.versionText") + " " + Messages.getString("DocSearch.version") + "\n\n" + Messages.getString("DocSearch.aboutString"));
            }
            else if (s.equals(dsOpen)) {
                doOpen();
            }
            else if (s.equals(dsSave)) {
                doSave();
            }
            else if (s.equals(dsSearchTips)) {
                showMessage(dsSearchTips, Messages.getString("DocSearch.searchTips"));
            }
            else if (s.equals(dsOpenInBrowse)) {
                doExternal(curPage);
            }
            else if (s.equals(dsBack)) {
                doBack();
            }
            else if (s.equals(dsDoNewIndex)) {
                doNewIndex();
            }
            else if (s.equals(dsReIndex)) {
                rebuildIndexes();
            }
            else if (s.equals(STOP)) {
                doStop();
            }
            else if (s.equals(dsDoSearch)) { 
                doThreadedSearch();
            }
            else if (s.equals(dsDoManageIndex)) {
                doManageIndexes();
                lastSearchedText = "";
            }
            else if (s.equals(dsImportIndex)) {
                getImportInfo();
            }
            else if (s.equals(dsBookmark) || s.equals(dsAddBookmark)) {
                doBookmark();
            }
            else if (s.equals(dsClearBookmarks)) {
                bookmarksList.clear();
                File bmf = new File(fEnv.getBookmarkFile());
                boolean wasCleared = true;
                String errString = "";
                if (bmf.exists()) {
                    try {
                        bmf.delete();
                    }
                    catch (Exception eF) {
                        wasCleared = false;
                        errString = eF.toString();
                    }
                }

                if (!wasCleared) {
                    showMessage(Messages.getString("DocSearch.errRemoBkMks"), errString);
                }
                else {
                    showMessage(Messages.getString("DocSearch.bmClrd"), Messages.getString("DocSearch.bmClrdMsg"));
                }
            }
            else if (s.equals(dsTpx)) {
                try {
                    setPage(fileString + helpPageString);
                }
                catch (Exception e) {
                    // error message
                    editorPane.setText(lastSearch);
                }
            }
            else if (s.equals(dsResults)) {
                editorPane.setContentType("text/html");
                editorPane.setText(lastSearch);
                editorPane.select(0, 0);
                iconButtons[5].setEnabled(false); // forward
                iconButtons[3].setEnabled(false); // back

                backList = new LinkedList();
                forwardList = new LinkedList();
                forwardPos = -1;
                backwardPos = -1;
                curPage = "results";
            }
            else if (s.equals(dsHome)) {
                editorPane.setContentType("text/html");
                if (hasStartPage) {
                    try {
                        setPage(fileString + startPageString);
                    }
                    catch (Exception e) {
                        // error message
                        editorPane.setText(lastSearch);
                    }

                    curPage = dsHome;
                }
                else {
                    editorPane.setText(lastSearch);
                    editorPane.select(0, 0);
                    curPage = "results";
                }

                iconButtons[5].setEnabled(false); // forward
                iconButtons[3].setEnabled(false); // back

                backList = new LinkedList();
                forwardList = new LinkedList();
                forwardPos = -1;
                backwardPos = -1;
            }
            else {
                if (s.startsWith("file:/") || s.startsWith("http")) {
                    setPage(s);
                    forwardPos = -1;
                    backwardPos = -1;
                    backList = new LinkedList();
                    forwardList = new LinkedList();
                    iconButtons[5].setEnabled(false); // forward
                    iconButtons[3].setEnabled(false); // back
                }
            }
        }
        catch (Exception e) {
            logger.error("handleEventCommand() action thread was stopped!", e);
        }
    }


    /**
     * Method actionPerformed
     * 
     * @param actionevent
     */
    public void actionPerformed(ActionEvent actionevent) {
        String a = actionevent.getActionCommand();
        GuiThread g = new GuiThread(this, a);
        g.start();
    }


    /**
     * Checks to see that a DocSearcherIndex has its lucene index folder
     * 
     * @return true if the lucene index folder for the index exists
     */
    private boolean hasIndex() {
        boolean returnBool = true;
        File indexFolder = new File(fEnv.getIndexDirectory());
        if (! indexFolder.exists()) {
            returnBool = false;
        }
        else if (env.isGUIMode()) {
            setStatus(idxFldr + " " + fEnv.getIndexDirectory() + " " + dsExists);
        }
        return returnBool;
    }


    /**
     * changes the label at the bottom of the frame to reflect ungoing progress,
     * etc...
     */
    public void setStatus(String toSet) {
        if (! isLoading && env.isGUIMode()) {
            dirLabel.setText(toSet);
        }
        else {
            logger.debug("setStatus() " + toSet);
        }
    }


    /**
     * Display's a question (details) and returns a 1 if no or 0 if yes is
     * answered
     * 
     * @return 0 for yes and 1 for no
     */
    public int getConfirmation(String details, String title) {
        int n = JOptionPane.showConfirmDialog(this, title, details, JOptionPane.YES_NO_OPTION);
        return n;
    }


    /**
     * Question dialog for yes or no that returns true for yes and false for no
     * 
     * @return true for yes and false for no
     */
    private boolean getConfirmationMessage(String title, String details) {
        MessageConfirmRunner mct = new MessageConfirmRunner(title, details, this);

        try {
            SwingUtilities.invokeAndWait(mct);

            if (mct.getReturnInt() == JOptionPane.YES_OPTION) {
                return true;
            }
        }
        catch (InterruptedException ie) {
            logger.fatal("getConfirmationMessage() failed with InterruptedException", ie);
        }
        catch (InvocationTargetException ite) {
            logger.fatal("getConfirmationMessage() failed with InvocationTargetException", ite);
        }
        
        return false;
    }


    /**
     * Displays a dialog for informational or error messages - invokes a
     * MessageRunner so as not to be on the dispatch (GUI) thread
     * 
     * @see MessageRunner
     */
    public void showMessage(String title, String details) {
        MessageRunner mesThread = new MessageRunner(title, details, this);
        try {
            SwingUtilities.invokeLater(mesThread);
        } catch (Exception e) {
            logger.error("showMessage() failed", e);
        }
    }


    /**
     * Does the actual work for Displaying an informational dialog - invoked via
     * a MessageRunner so as not to be on the dispatch (GUI) thread
     * 
     * @see MessageRunner
     */
    public void showMessageDialog(String title, String body) {
        if (! isLoading  &&  env.isGUIMode()) {
            int messageType = JOptionPane.INFORMATION_MESSAGE;
            if (title.toLowerCase().indexOf(dsErrLower) != -1) {
                messageType = JOptionPane.ERROR_MESSAGE;
            }

            pane = new JOptionPane(body, messageType);
            JDialog dialog = pane.createDialog(this, title);
            dialog.setVisible(true);
        }
        else {
            logger.info("showMessageDialog() \n* * * " + title + " * * *\n\t" + body);
        }
    }


    /**
     * Method getSearchIndexes
     * 
     * @return
     */
    private String getSearchedIndexes() {
        StringBuffer rb = new StringBuffer();

        // iterate over the di s
        int numIndexes = 0;
        if (!indexes.isEmpty()) {
            numIndexes = indexes.size();

            // add the items
            Iterator iterator = indexes.iterator();
            DocSearcherIndex curI;
            if (numIndexes > 0) {
                rb.append("<ul>");
            }
            while (iterator.hasNext()) {
                curI = ((DocSearcherIndex) iterator.next());
                if (curI.getShouldBeSearched()) {
                    rb.append("<li><font color = blue>");
                    rb.append(curI.getDescription());
                    rb.append("</font></li>");
                }
            }

            if (numIndexes > 0) {
                rb.append("</ul>");
            }
        }

        if (numIndexes == 0) {
            return "<p align = left><b>" + dsNone + "</b></p>";
        } else {
            return rb.toString();
        }
    }


    /**
     * Method screeForSize
     * 
     * @param hits
     * @param lowerSize
     * @param upperSize
     * @return
     */
    private ArrayList[] screenForSize(Hits hits, int lowerSize, int upperSize) {
        ArrayList[] returnList = new ArrayList[2];
        returnList[0] = new ArrayList();
        returnList[1] = new ArrayList();
        int tempSize = 0;
        for (int i = 0; i < hits.length(); i++) {
            try {
                tempSize = Integer.parseInt(hits.doc(i).get("size"));
                if ((tempSize >= lowerSize) && (tempSize <= upperSize)) {
                    returnList[0].add(hits.doc(i));
                    returnList[1].add(("" + hits.score(i)));
                }
            } catch (Exception eR) {
                setStatus(dsErrObtSi + " " + eR.toString());
            }
        }

        return returnList;
    }

    /**
     * Class PrintMIListener
     */
    public class PrintMIListener implements ActionListener {
        /**
         * Log4J logger
         */
        private Logger logger = Logger.getLogger(getClass().getName());

        /**
         * Implement from ActionListener
         */
        public void actionPerformed(ActionEvent evt) {
            PrinterJob pj = PrinterJob.getPrinterJob();
            pj.setJobName("docSearcher");
            pj.setPageable(vista);
            try {
                if (pj.printDialog()) {
                    pj.print();
                }
            }
            catch (PrinterException pe) {
                logger.fatal("actionPerformed() failed with PrinterException", pe);
                showMessage(dsErrPrint, pe.toString());
            }
        }
    }

    /**
     * Class Scale2Listener
     */
    public class Scale2Listener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
            vista.setScale(2.0, 2.0);
        }
    }

    /**
     * Class ScaleFitListener
     */
    public class ScaleFitListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
            vista.scaleToFit(false);
        }
    }

    /**
     * Class ScaleHalfListener
     * 
     * @author henschel
     * 
     */
    public class ScaleHalfListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
            vista.setScale(0.5, 0.5);
        }
    }

    /**
     * Class ScaleOffLister
     */
    public class ScaleOffListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
        }
    }

    /**
     * Class ScaleXListener
     */
    public class ScaleXListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
            vista.scaleToFitX();
        }
    }

    /**
     * Class ScaleYListener
     */
    public class ScaleYListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            vista = new JComponentVista(editorPane, new PageFormat());
            vista.scaleToFitY();
        }
    }


    /**
     * Method setSearching
     * 
     * @param toSet
     */
    public void setSearching(boolean toSet) {
        currentlySearching = toSet;
    }


    /**
     * Method doSearch
     * 
     * @param searchText
     */
    public void doSearch(String searchText) {
        setStatus(plsWait + " " + dsSchin + " --> " + searchText);
        setSearching(true);
        setIsWorking(true);
        int srchMaxPos = indexes.size() * 3;
        int curSrchPos = 0;
        if (srchMaxPos > 0) {
            pPanel.setMaxPos(srchMaxPos);
        }
        synchronized (this) {
            ArrayList[] sizeList = new ArrayList[2];
            sizeList[0] = new ArrayList();
            sizeList[1] = new ArrayList();
            String findText = "";
            if (phrase.isSelected()) {
                if (searchText.indexOf("\"") == -1) {
                    searchText = "\"" + searchText + "\"";
                }
            }
            // for each di - search and add the results
            int grandTotalHits = 0;
            int selectedFields = searchIn.getSelectedIndex();
            String sField = searchOpts[selectedFields];
            String tempSearchText = searchText;
            StringBuffer searchedIndexes = new StringBuffer();
            searchedIndexes.append("<ul>");
            StringBuffer hitBuf;
            StringBuffer tempBuf = new StringBuffer();
            StringBuffer bodyBuf = new StringBuffer();
            String curTitle = "";
            String curSize = "";
            String curAuthor = "";
            String curDate = "";
            String curFile = "";
            boolean isCdRomIdx = false;
            String curType = "";
            String curSummary = "";
            int numHits = 0;
            hitBuf = new StringBuffer();
            hitBuf.append("<html><head><title>");
            hitBuf.append(dsRsltsFoSch);
            hitBuf.append(" ");
            hitBuf.append(searchText);
            hitBuf.append("</title><body><h1 align=\"center\">");
            hitBuf.append(dsRsltsFoSch);
            hitBuf.append(" ");
            hitBuf.append("<strong><font color=\"blue\">");
            hitBuf.append(searchText);
            hitBuf.append("</font></strong></h1>");
            if (! env.isGUIMode()) {
                logger.info("doSearch() " + dsRsltsFoSch + " " + searchText);
            }
            // int curColor = 0;
            int curTypeInt = 0;
            // int numIndexes = 0;
            if (!indexes.isEmpty()) {
                try {
                    // numIndexes = indexes.size();
                    // add the items
                    Iterator iterator = indexes.iterator();
                    DocSearcherIndex curI;
                    while (iterator.hasNext()) {
                        curSrchPos++;
                        if (curSrchPos > 0) {
                            pPanel.setCurPos(curSrchPos);
                        }
                        curI = ((DocSearcherIndex) iterator.next());
                        isCdRomIdx = curI.isCdrom();
                        tempBuf = new StringBuffer();
                        if (curI.getShouldBeSearched()) {
                            searcher = new IndexSearcher(curI.getIndexPath());
                            if ((searchText.indexOf("(") != -1) || (searchText.indexOf("[") != -1)) {
                                findText = searchText;
                            } else {
                                if (selectedFields == 0) {
                                    findText = "+(+body:(" + tempSearchText + ") OR +title:(" + tempSearchText + "))";
                                } // body and title
                                else {
                                    findText = "+" + sField + ":(" + searchText + ")";
                                }
                                if (useAuthor.isSelected()) {
                                    findText += " AND +author:(" + authorField.getText() + ")";
                                }
                                if (useType.isSelected()) {
                                    findText += " AND +type:(" + fileTypesToGet[fileType.getSelectedIndex()] + ")";
                                }
                            } // end for a regular search
                            setStatus(dsSrchStr + ": " + findText + "...");
                            query = QueryParser.parse(findText, sField, new StandardAnalyzer());
                            if (useDate.isSelected()) {
                                DateFilter df = new DateFilter("mod_date", DateTimeUtils.getJDateFromString(fromField.getText()), DateTimeUtils.getJDateFromString(toField.getText()));
                                hits = searcher.search(query, df);
                            } else {
                                hits = searcher.search(query);
                            }
                            if (useSize.isSelected()) {
                                int fromInt = 1;
                                int toInt = 2;
                                try {
                                    fromInt = Integer.parseInt(sizeFromField.getText()) * 1024;
                                    toInt = Integer.parseInt(sizeToField.getText()) * 1024;
                                } catch (Exception eN) {
                                    setStatus(dsErrParseNums + " " + eN.toString());
                                }
                                sizeList = screenForSize(hits, fromInt, toInt);
                                numHits = sizeList[0].size();
                            } else {
                                numHits = hits.length(); // NOT A SIZE QUERY
                            }
                            searchedIndexes.append("<li> <font color=\"blue\">");
                            searchedIndexes.append(curI.getDescription());
                            searchedIndexes.append("</font> (<b>");
                            searchedIndexes.append(numHits);
                            searchedIndexes.append("</b>  &nbsp; ");
                            searchedIndexes.append(dsDox);
                            searchedIndexes.append(")</li>");
                            if (! env.isGUIMode()) {
                                logger.info("doSearch() " + dsIndex + ": " + curI.getDescription());
                            }
                            float curScore;
                            grandTotalHits += numHits;
                            tempBuf.append("<p align=\"center\"><b>");
                            tempBuf.append(numHits);
                            tempBuf.append("</b> &nbsp; ");
                            tempBuf.append(dsDocsFndInIndx);
                            tempBuf.append("<b>  &nbsp; ");
                            tempBuf.append(curI.getDescription());
                            tempBuf.append("</b></p>");
                            // curColor = 0;
                            curTypeInt = 0;
                            curSrchPos++;
                            if (curSrchPos > 0) {
                                pPanel.setCurPos(curSrchPos);
                            }
                            for (int i = 0; i < numHits; i++) {
                                if (i > maxNumHitsShown) {
                                    setStatus(dsMxNumHits + " (" + maxNumHitsShown + ") " + dsExceeded + " (" + numHits + ").");
                                    break;
                                }
                                //
                                if (!useSize.isSelected()) {
                                    curTitle = Utils.convertTextToHTML(hits.doc(i).get("title"));
                                    curSize = hits.doc(i).get("size");
                                    if (! curI.getIsWeb()) {
                                        if (!isCdRomIdx) {
                                            curFile = hits.doc(i).get("path");
                                        } else {
                                            curFile = hits.doc(i).get("URL");
                                            curFile = getCDROMPath(curFile);
                                        }
                                    } else {
                                        curFile = hits.doc(i).get("URL");
                                    }
                                    curType = hits.doc(i).get("type");
                                    curAuthor = hits.doc(i).get("author");
                                    if (curAuthor.equals("")) {
                                        curAuthor = dsUnk;
                                    }
                                    curDate = hits.doc(i).get("mod_date");
                                    if (curDate.equals("")) {
                                        curDate = dsUnk;
                                    } else {
                                        curDate = DateTimeUtils.getDateFormatNormal(curDate);
                                    }
                                    curTypeInt = FileTypeUtils.getFileType(curType);
                                    curScore = hits.score(i);
                                    curSummary = Utils.convertTextToHTML(hits.doc(i).get("summary"));
                                }
                                else {
                                    curTitle = Utils.convertTextToHTML(((Document) sizeList[0].get(i)).get("title"));
                                    curSize = ((Document) sizeList[0].get(i)).get("size");
                                    if (! curI.getIsWeb()) {
                                        curFile = ((Document) sizeList[0].get(i)).get("path");
                                    } else {
                                        curFile = ((Document) sizeList[0].get(i)).get("URL");
                                    }
                                    curType = ((Document) sizeList[0].get(i)).get("type");
                                    curAuthor = ((Document) sizeList[0].get(i)).get("author");
                                    if (curAuthor.equals("")) {
                                        curAuthor = dsUnk;
                                    }
                                    curDate = ((Document) sizeList[0].get(i)).get("mod_date");
                                    if (curDate.equals("")) {
                                        curDate = dsUnk;
                                    } else {
                                        curDate = DateTimeUtils.getDateFormatNormal(curDate);
                                    }
                                    curTypeInt = FileTypeUtils.getFileType(curType);
                                    curScore = 1;
                                    try {
                                        curScore = Float.parseFloat(((String) sizeList[1].get(i)));
                                    } catch (Exception eF) {
                                        setStatus(dsErrParseScore + " " + eF.toString());
                                    }
                                    curSummary = ((Document) sizeList[0].get(i)).get("summary");
                                }
                                //
                                // add it to our page - doc size title score
                                tempBuf.append("<p align=\"left\">");
                                if (! curI.getIsWeb()) {
                                    tempBuf.append("<a href=\"");
                                    tempBuf.append(fileString);
                                    tempBuf.append(curFile);
                                    tempBuf.append("\">");
                                }
                                else {
                                    tempBuf.append("<a href=\"");
                                    tempBuf.append(curFile);
                                    tempBuf.append("\">");
                                }
                                if (hasIcons) {
                                    switch (curTypeInt) {
                                        case FileType.HTML: // html
                                            tempBuf.append(htmlTag);
                                            break;
                                        case FileType.MS_WORD: // ms word
                                            tempBuf.append(wordTag);
                                            break;
                                        case FileType.MS_EXCEL: // ms excel
                                            tempBuf.append(excelTag);
                                            break;
                                        case FileType.PDF: // pdf
                                            tempBuf.append(pdfTag);
                                            break;
                                        case FileType.RTF: // rtf
                                            tempBuf.append(rtfTag);
                                            break;
                                        case FileType.OO_WRITER: // openoffice writer
                                            tempBuf.append(ooWriterTag);
                                            break;
                                        case FileType.OO_IMPRESS: // openoffice impress
                                            tempBuf.append(ooImpressTag);
                                            break;
                                        case FileType.OO_CALC: // openoffice calc
                                            tempBuf.append(ooCalcTag);
                                            break;
                                        case FileType.OO_DRAW: // openoffice draw
                                            tempBuf.append(ooDrawTag);
                                            break;
                                        case FileType.OPENDOCUMENT_TEXT: // opendocument text
                                            tempBuf.append(openDocumentTextTag);
                                            break;
                                        default: // text
                                            tempBuf.append(textTag);
                                            break;
                                    }
                                } else {
                                    tempBuf.append(curType);
                                }
                                tempBuf.append(" ");
                                tempBuf.append(curTitle);
                                tempBuf.append("</a><br>");
                                tempBuf.append(curSummary);
                                tempBuf.append("<font color=\"green\"><br><em>");
                                // TODO format date with locale
                                tempBuf.append(curDate);
                                tempBuf.append(", ");
                                tempBuf.append(Utils.getKStyle(curSize));
                                tempBuf.append("bytes, ");
                                tempBuf.append(curAuthor);
                                tempBuf.append(", <b>");
                                tempBuf.append(Utils.getPercentFromFloat(curScore));
                                tempBuf.append("</b></em></font><br><font color=\"gray\">");
                                tempBuf.append(curFile);
                                tempBuf.append("</font>");
                                tempBuf.append("</p>");
                                if (! env.isGUIMode()) {
                                    logger.info("doSearch() \n\n* " + curTitle + "\n" + curSummary + "\n" + curDate + ", " + Utils.getKStyle(curSize) + "bytes, " + curAuthor + ", " + Utils.getPercentFromFloat(curScore) + "\n" + curFile);
                                }
                            } // end for hits
                            // now add our results
                            curSrchPos++;
                            if (curSrchPos > 0) {
                                pPanel.setCurPos(curSrchPos);
                            }
                            // add the footer
                            bodyBuf.append(tempBuf.toString());
                        } // end if shouldbesearched
                        else {
                            tempBuf.append("<p align=\"left\">");
                            tempBuf.append(dsIndex);
                            tempBuf.append("  &nbsp; <b>");
                            tempBuf.append(curI.getDescription());
                            tempBuf.append("</b>  &nbsp; ");
                            tempBuf.append(dsWasNotSearched);
                            tempBuf.append("</p>");
                            bodyBuf.append(tempBuf.toString());
                        }
                        if (curI.getShouldBeSearched()) {
                            searcher.close();
                        }
                    } // end while hasmore indexes
                    // finish up the page
                    searchedIndexes.append("</ul>");
                    hitBuf.append("<p align=\"left\"><strong>");
                    hitBuf.append(grandTotalHits);
                    hitBuf.append("</strong>  &nbsp; ");
                    hitBuf.append(dsTotalDocsFndIndx);
                    hitBuf.append(":</p>");
                    hitBuf.append(searchedIndexes.toString());
                    hitBuf.append(bodyBuf);
                    hitBuf.append("</body></html>");
                    if (! env.isGUIMode()) {
                        logger.info("doSearch() \n" + dsTotHits + ": " + grandTotalHits);
                    }
                    lastSearch = hitBuf.toString();
                    if (env.isGUIMode()) {
                        editorPane.setText(lastSearch);
                        editorPane.select(0, 0);
                        int numS = searchField.getItemCount();
                        boolean inThere = false;
                        String tmpSrchTxt = "";
                        if (numS > 0) {
                            for (int i = 1; i < numS; i++) {
                                tmpSrchTxt = (String) searchField.getItemAt(i);
                                if (tmpSrchTxt != null) {
                                    if (tmpSrchTxt.equals(searchText)) {
                                        inThere = true;
                                    }
                                }
                            }
                        }
                        if (!inThere) {
                            searchField.addItem(searchText);
                        }
                        searchField.setSelectedIndex(searchField.getItemCount() - 1);
                        vista = new JComponentVista(editorPane, new PageFormat());
                        forwardPos = -1;
                        backwardPos = -1;
                        backList = new LinkedList();
                        addToBackList(curPage);
                        curPage = "results";
                        forwardList = new LinkedList();
                    } // end if useGui
                } // end for try
                catch (IOException ioe) {
                    logger.fatal("doSearch() failed with IOException", ioe);
                    showMessage(dsErrPrfSrch, dsCrptdIdx + " :\n" + ioe.toString());
                }
                catch (NullPointerException npe) {
                    logger.fatal("doSearch() failed with NullPointerException", npe);
                    showMessage(dsErrPrfSrch, dsCrptdIdx + " :\n" + npe.toString());
                }
                catch (Exception e) {
                    logger.fatal("doSearch() failed with Exception", e);
                    showMessage(dsErrPrfSrch, e.toString());
                }
                setStatus(SEARCH_COMPLETE);
                setSearching(false);
            }
            else {
                showMessage(dsErrPrfSrch, dsMkIdx);
            }
        }

        setIsWorking(false);
        pPanel.reset();
    }


    /**
     * Method loadFile
     * 
     * @param fileToLoad
     * @return
     */
    private StringBuffer loadFile(String fileToLoad) {
        if (logger.isDebugEnabled()) {
            logger.debug("loadFile('" + fileToLoad + "') entered");
        }

        setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

        // raed file
        StringBuffer returnBuffer = new StringBuffer();
        FileReader fileReader = null;
        try {
            File readFile = new File(fileToLoad);
            if (readFile.exists() && ! readFile.isDirectory()) {
                fileReader = new FileReader(fileToLoad);
                int i;
                while ((i = fileReader.read()) != -1) {
                    returnBuffer.append((char) i);
                }

                fileReader.close();
            }
            else {
                returnBuffer.append(" ** FILE NOT FOUND OR FILE IS A DIRECTORY [").append(fileToLoad).append("] **\n");
            }
        }
        catch (IOException ioe) {
            logger.fatal("loadFile() failed", ioe);
            showMessage(dsErrLdgFi, "\n" + fileToLoad + "\n\n : " + ioe.toString());
        }
        finally {
            if (fileReader != null) {
                try {
                    fileReader.close();
                }
                catch (IOException ioe) {
                    logger.fatal("loadFile() can't close FileReader", ioe);
                }
            }
        }

        setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

        return returnBuffer;
    }


    /**
     * setPage
     * 
     * @param pageToSet
     * @return
     */
    private boolean setPage(String pageToSet) {

        try {
            if (FileTypeUtils.isFileTypeHTML(pageToSet) || FileTypeUtils.isFileTypeText(pageToSet)) {
                editorPane.setContentType("text/html");
                editorPane.setPage(fileString + blankFile);
            }
        }
        catch (NullPointerException npe) {
            logger.fatal("setPage() failed", npe);
            setStatus(dsErrSetPa + " : " + npe.toString() + "\n" + pageToSet);
        }
        catch (IOException ioe) {
            logger.fatal("setPage() failed", ioe);
            setStatus(dsErrSetPa + " : " + ioe.toString() + "\n" + pageToSet);

        }

        boolean returnBool = true;
        // String loadString = pageToSet;
        if (pageToSet.equals("home")) {
            setStatus(dsLdg + " : *" + pageToSet + "*");
            editorPane.setContentType("text/html");
            if (hasStartPage) {
                try {
                    editorPane.setPage(fileString + startPageString);
                }
                catch (Exception eL) {
                    // error message
                    editorPane.setText(lastSearch);
                }
            }
            else {
                editorPane.setText(lastSearch);
            }
            editorPane.select(0, 0);
            curPage = "home";
        }
        else if (pageToSet.equals("results")) {
            setStatus(dsLdg + " : *" + pageToSet + "*");
            editorPane.setContentType("text/html");
            editorPane.setText(lastSearch);
            editorPane.select(0, 0);
            curPage = "results";
        }
        else {
            if (FileTypeUtils.isFileTypeHTML(pageToSet) || FileTypeUtils.isFileTypeText(pageToSet)) {
                if (FileTypeUtils.isFileTypeHTML(pageToSet)) {
                    editorPane.setContentType("text/html");
                }
                else if (FileTypeUtils.isFileTypeText(pageToSet)) {
                    editorPane.setContentType("text/plain");
                }
                try {
                    // set the page
                    if (pageToSet.startsWith("file:/")) {
                        pageToSet = pageToSet.substring(6, pageToSet.length());
                        editorPane.setPage(fileString + pageToSet);
                    }
                    else if (pageToSet.startsWith("http:")) {
                        editorPane.setPage(pageToSet);
                    }
                    else if (pageToSet.startsWith("ftp")) {
                        editorPane.setPage(pageToSet);
                    }
                    else {
                        editorPane.setPage(fileString + pageToSet);
                    }
                    setStatus(dsLoaded + " " + pageToSet);
                    curPage = pageToSet;
                }
                // end for try
                catch (Exception e) {
                    logger.fatal("setPage() failed", e);
                    returnBool = false;
                    showMessage(dsErrLdgPa, "\n" + pageToSet + e.toString());
                } // end for catch
            } // end for isHTML
            else {
                doExternal(pageToSet);
            }
        } // end for actual link

        if (returnBool) {
            curPage = pageToSet;
        }
        return returnBool;
    }


    /**
     * Method doBack
     */
    private void doBack() {
        int backSize = backList.size();
        String oldPage = curPage;
        String reopenPage = "";
        if (backwardPos < (backSize - 1)) {
            // go back
            backwardPos++;
            reopenPage = (String) backList.get(backwardPos);
            if (setPage(reopenPage)) {
                addToForwardList(oldPage);
                if (forwardPos > -1)
                    forwardPos--;
            } else
                backwardPos--;

            if (backwardPos == (backSize - 1))
                iconButtons[3].setEnabled(false);
        } else
            iconButtons[3].setEnabled(false); // back button
    }


    private void doForward() {
        int fwdSize = forwardList.size();
        // String oldPage = curPage;
        String reopenPage = "";
        if (forwardPos < (fwdSize - 1)) {
            // go back
            forwardPos++;
            reopenPage = (String) forwardList.get(forwardPos);
            if (setPage(reopenPage)) {
                // addToBackList(oldPage);
                if (backwardPos > -1)
                    backwardPos--;
                // addToBackList(oldPage);
            } else
                forwardPos--;
            if ((forwardPos == (fwdSize - 1)))
                iconButtons[5].setEnabled(false);
        } else
            iconButtons[5].setEnabled(false); // forward button
    }


    private void addToForwardList(String toAdd) {
        forwardList.add(0, toAdd);
        iconButtons[5].setEnabled(true); // forward button
    }


    private void addToBackList(String toAdd) {
        if ((toAdd.startsWith("file://")) && (!toAdd.startsWith("file:///"))) {
            toAdd = "file:///" + toAdd.substring(6, toAdd.length());
        }
        backList.add(0, toAdd);
        if (hasIcons) {
            iconButtons[3].setEnabled(true); // backward button
            iconButtons[5].setEnabled(false); // forward button
        }
    }


    private void doOpen() {
        JFileChooser fdo = new JFileChooser();
        fdo.setCurrentDirectory(new File(defaultSaveFolder));
        int fileGotten = fdo.showDialog(this, dsOpen);
        if (fileGotten == JFileChooser.APPROVE_OPTION) {
            File file = fdo.getSelectedFile();
            String fileName = file.toString();
            // get document stream and save it
            if (!fileName.startsWith("http")) {
                setPage(fileString + fileName);
            } else
                setPage(fileName);
        }
        // end if approved
    }


    private void doSave() {
        setStatus(dsSave);
        // defaultSaveFolder
        JFileChooser fds = new JFileChooser();
        fds.setDialogTitle(dsSave);
        boolean aWebPage = false;
        String saveName = "";
        if (curPage.equals("results"))
            saveName = "results.htm";
        else if (curPage.equals("home"))
            saveName = "home.htm";
        else {
            if (FileTypeUtils.isFileTypeHTML(curPage)) {
                aWebPage = true;
            }
            saveName = Utils.getNameOnly(curPage);
        }
        saveName = FileUtils.addFolder(defaultSaveFolder, saveName);
        fds.setCurrentDirectory(new File(defaultSaveFolder));
        fds.setSelectedFile(new File(saveName));
        int fileGotten = fds.showDialog(this, dsSave);
        if (fileGotten == JFileChooser.APPROVE_OPTION) {
            File file = fds.getSelectedFile();
            String fileName = file.toString();
            setStatus(dsSave + fileName);

            // get document stream and save it
            String saveText = editorPane.getText();
            int textLen = saveText.length();
            char curChar = ' ';
            try {
                File saveFile = new File(fileName);
                FileWriter filewriter = new FileWriter(saveFile);
                PrintWriter pw = new PrintWriter(filewriter);
                for (int i = 0; i < textLen; i++) {
                    curChar = saveText.charAt(i);
                    pw.print(curChar);
                }
                // end for writing text

                filewriter.close();
                pw.close();
            } catch (Exception eR) {
                showMessage(dsErrSaFi, "\n" + fileName);
            }
        }
        // end if approved
    }


    private void doExit() {
        try {
            if (!isCDSearchTool) {
                saveIndexes();
                saveHandlers();
                saveSettings();
            }
        }
        catch (Exception eR) {
            showMessage(dsErrSaFi, eR.toString());
        }
        finally {
            System.exit(0);
        }
    }


    private void saveHandlers() {
        // saves handler info into html table
        if (!handlerList.isEmpty()) {
            // int numHndlrs = handlerList.size();
            StringBuffer sB = new StringBuffer();
            sB.append("<html><head><title>DocSearcher File Handler Type Listing</title>");
            sB.append("<body><h1>DocSearcher File Handler Type Listing</h1><p align = left>");
            sB.append("Listed below are the file type handlers used to open various links by DocSearcher.</p>");
            sB.append("<table border = 1>");
            // add the items
            Iterator iterator = handlerList.iterator();
            docTypeHandler dh;
            while (iterator.hasNext()) {
                dh = ((docTypeHandler) iterator.next());
                sB.append("<tr>");
                sB.append("<td>");
                sB.append(dh.getExtension());
                sB.append("</td>");
                sB.append("<td>");
                sB.append(dh.getDesc());
                sB.append("</td>");
                sB.append("<td>");
                sB.append(dh.getApp());
                sB.append("</td>");
                sB.append("</tr>");
            }
            sB.append("</table></body></html>");
            FileUtils.saveFile("handlers_list.htm", fEnv.getWorkingDirectory(), sB);
        } // has items to save
    } // end for saveHandlers


    private void saveIndexes() {
        if (!indexes.isEmpty()) {
            // int numIndexes = indexes.size();
            StringBuffer sB = new StringBuffer();
            sB.append("<html><head><title>DocSearcher Index Listing</title><meta name=\"robots\" content=\"noindex,nofollow\"></head>");
            sB.append("<body><h1>DocSearcher Index Listing</h1><p align = left>");
            sB.append("Listed below are the paths and whether they are to be searched by default.</p>");
            sB.append("\n<table border = 1>\n");
            // add the items
            Iterator iterator = indexes.iterator();
            DocSearcherIndex curI;
            while (iterator.hasNext()) {
                curI = ((DocSearcherIndex) iterator.next());
                sB.append("\n<tr>");
                sB.append("\n<td>");
                sB.append(curI.getDescription());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getPath());
                sB.append("</td>");
                sB.append("\n<td>");
                if (curI.getShouldBeSearched())
                    sB.append("0");
                else
                    sB.append("1");
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getDepth());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getIndexPath());
                sB.append("</td>");
                // now the isWeb stuff and date
                sB.append("\n<td>");
                if (curI.getIsWeb())
                    sB.append("true");
                else
                    sB.append("false");

                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getMatch());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getReplace());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getLastIndexed());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getIndexPolicy());
                sB.append("</td>");
                sB.append("\n<td>");
                sB.append(curI.getArchiveDir());
                sB.append("</td>");
                sB.append("</tr>\n");
            }
            // end of iteration

            // close up the html
            sB.append("\n</table></body></html>");
            FileUtils.saveFile("index_list.htm", fEnv.getWorkingDirectory(), sB);

            // save the file
        }
        // end for not empty

        if (!bookmarksList.isEmpty()) {
            // int numIndexes = bookmarksList.size();
            StringBuffer sB = new StringBuffer();
            sB.append("<html><head><title>DocSearcher Bookmark Listing</title>");
            sB.append("<body><h1>DocSearcher Bookmark Listing</h1><p align = left>");
            sB.append("Listed below are the bookmarks for DocSearcher.</p>");
            sB.append("<table border = 1>");

            // add the items
            Iterator iterator = bookmarksList.iterator();
            SimpleBookmark  curI;
            while (iterator.hasNext()) {
                curI = ((SimpleBookmark) iterator.next());
                sB.append("<tr>");
                sB.append("<td>");
                sB.append(curI.getDescription());
                sB.append("</td>");
                sB.append("<td>");
                sB.append(curI.getURL());
                sB.append("</td>");
                sB.append("</tr>");
            }

            sB.append("</table></body></html>");
            FileUtils.saveFile("bookmarks.htm", fEnv.getWorkingDirectory(), sB);
        }
        // end for bookmarks not empty
    }


    /**
     * Loads the DocSearcher indexes
     */
    private void loadIndexes() {
        // check for indexFile
        int numIndexes = 0;
        File testIndex;
        String indexFileName = "";
        if (isCDSearchTool) {
            indexFileName = cdRomIdxList;
            logger.info("loadIndexes() Using Index information on CD : " + cdRomIdxList);
        }
        else {
            logger.info("loadIndexes() Loading NON - CD oriented indexes from " + fEnv.getIndexListFile());
            indexFileName = fEnv.getIndexListFile();
        }
        testIndex = new File(indexFileName);
        StringBuffer errS = new StringBuffer();
        boolean loadErr = false;
        DocSearcherIndex curI;
        File tempFile;
        String tempFileString = "";
        String tempIndexerPath = "";
        String tempDesc = "";
        int tempDepth = 0;
        int updatePolicy = 0;
        String updateStr = "";
        int tempSbd = 0;
        boolean tempBool = false;
        boolean tempWebBool = false;
        String tempMatchStr = "";
        boolean tempIsCdrom = false;
        String tempIsWeb = "";
        String tempReplace = "";
        String tempMatch = "";
        String tempDateStr = "";
        String tempArch = "";
        if (testIndex.exists()) {
            Table tempTable = new Table(11, 100);
            tempTable.htmlLoad(indexFileName, "");
            int numI = tempTable.colSize();
            // parse it
            for (int i = 0; i < numI; i++) {
                //
                try {
                    tempDesc = tempTable.inItem(0, i);
                    tempFileString = tempTable.inItem(1, i);
                    tempSbd = Integer.parseInt(tempTable.inItem(2, i));
                    tempIndexerPath = tempTable.inItem(4, i);
                    // isWeb content
                    tempIsWeb = tempTable.inItem(5, i);
                    tempWebBool = false;
                    tempReplace = "";
                    tempMatch = "";
                    tempDateStr = "";
                    if (tempIsWeb != null) {
                        if (tempIsWeb.equals("true")) {
                            tempWebBool = true;
                            tempMatch = tempTable.inItem(6, i);
                            tempReplace = tempTable.inItem(7, i);
                        }
                    }
                    // CDROM Stuff tempIsCdrom tempReplaceStr
                    tempMatchStr = tempTable.inItem(6, i);
                    if (tempMatchStr != null) {
                        if (tempMatchStr.startsWith("[cdrom]")) {
                            tempMatch = tempTable.inItem(6, i);
                            tempIsCdrom = true;
                            tempReplace = tempTable.inItem(7, i);
                            // cdRomIdxDir
                            if (isCDSearchTool) {
                                tempIndexerPath = FileUtils.addFolder(cdRomIdxDir, Utils.getNameOnly(tempIndexerPath));
                            }
                            logger.info("loadIndexes() Using CDROM Lucene index path: " + tempIndexerPath);
                        }
                    }
                    tempDateStr = tempTable.inItem(8, i);
                    updateStr = tempTable.inItem(9, i);
                    if (updateStr == null) {
                        updatePolicy = 0;
                    } else {
                        updatePolicy = Integer.parseInt(updateStr);
                    }

                    if (tempDateStr == null) {
                        tempDateStr = DateTimeUtils.getToday();
                    }

                    if (tempSbd == 1) {
                        tempBool = false;
                    } else {
                        tempBool = true;
                    }

                    tempArch = tempTable.inItem(10, i);
                    if (tempArch == null) {
                        tempArch = fEnv.getArchiveDirectory();
                    }

                    tempDepth = Integer.parseInt(tempTable.inItem(3, i));
                    tempFile = new File(tempFileString);
                    if (tempFileString.toLowerCase().endsWith(".zip")) {
                        curI = new DocSearcherIndex(tempFileString, tempDesc, tempBool, tempDepth, tempIndexerPath, tempWebBool, tempMatch, tempReplace, tempDateStr, updatePolicy, tempArch);
                        indexes.add(curI);
                        if (env.isGUIMode()) {
                            setStatus(dsIndex + " " + curI.getDescription() + " : " + DateTimeUtils.getDaysOld(curI.getLastIndexed()) + " " + dsDaysOld + " : " + curI.getLastIndexed());
                        }

                        numIndexes++;
                    }

                    else if (tempIsCdrom) {
                        curI = new DocSearcherIndex(tempFileString, tempDesc, tempBool, tempDepth, tempIndexerPath, tempWebBool, tempMatch, tempReplace, tempDateStr, updatePolicy, tempArch);
                        indexes.add(curI);
                        setStatus(dsIndex + " " + curI.getDescription() + " : " + DateTimeUtils.getDaysOld(curI.getLastIndexed()) + " " + dsDaysOld + " : " + curI.getLastIndexed());
                        numIndexes++;
                    }

                    else if ((tempFile.exists()) || (tempFileString.startsWith("http"))) {
                        curI = new DocSearcherIndex(tempFileString, tempDesc, tempBool, tempDepth, tempIndexerPath, tempWebBool, tempMatch, tempReplace, tempDateStr, updatePolicy, tempArch);
                        indexes.add(curI);
                        setStatus(dsIndex + " " + curI.getDescription() + " : " + DateTimeUtils.getDaysOld(curI.getLastIndexed()) + " " + dsDaysOld + " : " + curI.getLastIndexed());
                        numIndexes++;
                    } else {
                        loadErr = true;
                        errS.append(tempFileString + "\n\t" + dsNotExist + "\n\n");
                    }
                    // end for file doesn't exist
                } catch (Exception eN) {
                    loadErr = true;
                    errS.append(eN.toString() + "\n\n");
                }
            }
        }

        if (numIndexes == 0) {
            loadErr = true;
            errS.append(dsMkIdx);
        }

        // now load the bookmarks
        // from the bookmarksFile
        File testBMF = new File(fEnv.getBookmarkFile());
        if (testBMF.exists()) {
            Table tempTable = new Table(2, 200);
            tempTable.htmlLoad(fEnv.getBookmarkFile(), "");
            int numI = tempTable.colSize();

            // parse it
            for (int i = 0; i < numI; i++) {
                addNewBookmark(new SimpleBookmark(tempTable.inItem(1, i), tempTable.inItem(0, i)));
            }
        }

        if (loadErr)
            showMessage(Messages.getString("DocSearch.errLdgIdx"), errS.toString());
        else
            setStatus(numIndexes + " " + Messages.getString("DocSearch.totalIdxs"));
    }


    /**
     * ensures default properties files are present for user settings
     */
    private void checkDefaults() {
        File workingDirFile = new File(fEnv.getWorkingDirectory());
        if (!workingDirFile.exists())
            workingDirFile.mkdir();
        // end for creating the working directory
        File defaultSaveFolderFile = new File(defaultSaveFolder);
        if (!defaultSaveFolderFile.exists())
            defaultSaveFolderFile.mkdir();
        // end for creating the working directory
        blankFile = FileUtils.addFolder(fEnv.getWorkingDirectory(), "blank_page.htm");
        File blankPageFile = new File(blankFile);
        if (! blankPageFile.exists()) {
            StringBuffer bp = new StringBuffer();
            bp.append("<html><head><title>")
                .append(loadingP)
                .append("</title></head><body><h1>")
                .append(loadingP)
                .append("</h1></body></html>");
            FileUtils.saveFile("blank_page.htm", fEnv.getWorkingDirectory(), bp);
        }
        File indexFolder = new File(fEnv.getIndexDirectory());
        if (!indexFolder.exists()) {
            setStatus(fEnv.getIndexDirectory() + " " + dsNotExist);
            indexFolder.mkdir();
        }
    }


    /**
     * creates a new docSearcher index
     */
    private void createNewIndex(DocSearcherIndex di, boolean isCdRomIndx) throws IOException {
        setStatus(dsIdxg + " (" + di.getIndexPath() + ") ");
        setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        checkDefaults();
        StringBuffer failedBuf = new StringBuffer();
        String indexDirNew = di.getIndexPath();
        File indexFolder = new File(indexDirNew);
        long curFileSizeBytes = 0;
        int addedSuccessfully = 0;
        StringBuffer noRobotsBuf = new StringBuffer();
        noRobotsBuf.append(dsMetaFiles);
        int numNoIndex = 0;
        boolean newIndex = false;
        if (!indexFolder.exists()) {
            setStatus(indexDirNew + " " + dsNotExist);
            indexFolder.mkdir();
            newIndex = true;
        }
        // BUILD THE INDEX
        File contentFolder = new File(di.getPath());
        int totalFolders = 1;
        int totalFiles = 0;
        int numErrors = 0;
        // String urlStr = "";
        // String dateStr = "";
        // File tempDFile;
        int curSize = 1;
        if (contentFolder.exists()) {
            ArrayList folderList = new ArrayList();
            folderList.add(di.getPath()); // add in our contentDir
            String curFolderString = di.getPath();
            String[] filesString;
            String[] foldersString;
            File curFolderFile;
            int curItemNo = 0;
            int lastItemNo = 0;
            int numFiles = 0;
            int numFolders = 0;
            int curSubNum = 0;
            int startSubNum = Utils.countSlash(di.getPath());
            int maxSubNum = startSubNum + di.getDepth();
            // creating the index
            IndexWriter writer = new IndexWriter(indexDirNew, new StandardAnalyzer(), newIndex);
            // writer.setUseCompoundFile(true);
            do {
                // create our folder file
                curFolderString = (String) folderList.get(curItemNo);
                curFolderFile = new File(curFolderString);
                curSubNum = Utils.countSlash(curFolderString);
                try {
                    // handle any subfolders --> add them to our folderlist
                    foldersString = curFolderFile.list(ff);
                    numFolders = foldersString.length;
                    for (int i = 0; i < numFolders; i++) {
                        // add them to our folderlist
                        String curFold = curFolderString + pathSep + foldersString[i] + pathSep;
                        curFold = Utils.replaceAll(pathSep + pathSep, curFold, pathSep);
                        folderList.add(curFold);
                        lastItemNo++;
                        totalFolders++;
                        // debug output
                        setStatus(dsFndFldr + " " + curFold);
                    }
                    // end for having more than 0 folder
                }
                catch (Exception e) {
                    logger.fatal("createNewIndex() failed", e);
                    setStatus(curFolderString + " : " + e.toString());
                }

                // add our files
                try {
                    filesString = curFolderFile.list(wf);
                    numFiles = filesString.length;
                    logger.info("createNewIndex() Indexing " + numFiles + " files...");
                    for (int i = 0; i < numFiles; i++) {
                        // add them to our folderlist
                        String curFi = curFolderString + pathSep + filesString[i];
                        curFi = Utils.replaceAll(pathSep + pathSep, curFi, pathSep);
                        curFileSizeBytes = FileUtils.getFileSize(curFi);
                        if (curFileSizeBytes > getMaxFileSize()) {
                            setStatus(dsFileTooBig + " (" + curFileSizeBytes + ") " + filesString[i]);
                        }
                        else { // file size is not too big
                            setStatus(plsWait + " " + curFi + " # " + curSize);
                            curSize++;
                            addedSuccessfully = idx.addDocToIndex(curFi, writer, di, isCdRomIndx, null);
                            switch (addedSuccessfully) {
                                case 1: // error
                                    numErrors++;
                                    if (numErrors < 8) {
                                        failedBuf.append("\n");
                                        failedBuf.append(curFi);
                                    }
                                    break;
                                case 2: // meta robots = noindex
                                    numNoIndex++;
                                    if (numNoIndex < 8) {
                                        noRobotsBuf.append("\n");
                                        noRobotsBuf.append(curFi);
                                    }
                                    break;
                                default: // OK
                                    totalFiles++;
                                    break;
                            } // end of switch
                        } // end for not skipping, file size is not too big
                    }
                    // end for files
                }
                // end of trying to get files
                catch (Exception e) {
                    logger.error("createNewIndex() failed", e);
                    setStatus(dsErr + " " + e.toString());
                }
                // increment our curItem
                folderList.set(curItemNo, null); // remove memory overhead as
                // you go!
                curItemNo++;
                if (curSubNum >= maxSubNum) {
                    break;
                }
            }
            while (curItemNo <= lastItemNo);

            writer.close(); // close the writer
            indexes.add(di);
        }
        else {
            hasErr = true;
            errString = fEnv.getContentDirectory() + " " + dsNotExist;
        }
        // end for content dir Missing
        if (hasErr) {
            showMessage(Messages.getString("DocSearch.errCreatingIdx"), errString);
        }
        else {
            StringBuffer resultsBuf = new StringBuffer();
            resultsBuf.append(Messages.getString("DocSearch.addedToIdx"));
            resultsBuf.append(di.getDescription());
            resultsBuf.append("\" ");
            resultsBuf.append(totalFiles);
            resultsBuf.append(" ");
            resultsBuf.append(Messages.getString("DocSearch.filesFm"));
            resultsBuf.append(" ");
            resultsBuf.append(totalFolders);
            resultsBuf.append(" ");
            resultsBuf.append(Messages.getString("DocSearch.stgIn"));
            resultsBuf.append(" ");
            resultsBuf.append(di.getPath());
            resultsBuf.append("\n\n");
            resultsBuf.append(Messages.getString("DocSearch.forAdepthOf"));
            resultsBuf.append(" ");
            resultsBuf.append(di.getDepth());
            resultsBuf.append(".");
            if (numErrors > 0) {
                resultsBuf.append("\n" + numErrors);
                resultsBuf.append(" ");
                resultsBuf.append(Messages.getString("DocSearch.filesNotIdxd"));
                resultsBuf.append(failedBuf.toString());
            }

            if (numNoIndex > 0) {
                resultsBuf.append("\n\n" + numNoIndex);
                resultsBuf.append(dsMetaFiles);
                resultsBuf.append(noRobotsBuf.toString());
            }

            showMessage(dsIdxCrtd, resultsBuf.toString());
        }

        setStatus(dsIdxCrtd);
        setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }


    /**
     * creates a new index
     */
    private void doNewIndex() {
        NewIndexDialog nid = new NewIndexDialog(this, dsDoNewIndex, true);
        nid.init();
        nid.setVisible(true);
        if (nid.getConfirmed()) {
            //
            String descD = nid.getDescFieldText();
            String noUnd = Utils.replaceAll(" ", descD, "_");
            boolean isWeb = nid.isWebSelected();
            boolean isCdRomIndx = nid.isCDSelected();
            String replace = nid.replaceFieldText();
            String match = nid.matchFieldText();
            int policy = nid.getPolicy();
            try {
                createNewIndex(new DocSearcherIndex(nid.startFieldText(), descD, nid.sbdSelected(), nid.getSDChoice(), FileUtils.addFolder(fEnv.getIndexDirectory(), noUnd), isWeb, match, replace, policy, nid.archiveFieldText()), isCdRomIndx);
                // debug
                if (isCdRomIndx) {
                    logger.info("doNewIndex() CD Idx.. replace is : " + replace + ", match: " + match);
                }
            }
            catch (Exception eS) {
                showMessage(Messages.getString("DocSearch.errCreatingIdx"), eS.toString());
            }
        }
    }


    private void addNewBookmark(SimpleBookmark sbm) {
        bookmarksList.add(sbm);
        JMenuItem bmi = new JMenuItem(sbm.getDescription());
        bmi.setActionCommand(sbm.getURL());
        bmi.addActionListener(this);
        bookMarkMenu.add(bmi);
    }


    private void rebuildIndexes() {
        if (!indexes.isEmpty()) {
            Iterator iterator = indexes.iterator();
            DocSearcherIndex di;
            while (iterator.hasNext()) {
                di = ((DocSearcherIndex) iterator.next());
                idx.updateIndex(di);
            }
        }
        setStatus(dsIdxsRblt);
    }


    /**
     * Method look for some browsers existed on the system
     *
     * TODO why this method call every program start 
     *
     * @return  browser file string
     */
    private String getBrowserFile() {
        File testExist;
        String returnString = "";

        switch (env.getOSType()) {
            case OSType.WIN_32: // windows
                returnString = "C:\\Program Files\\Microsoft Internet\\Iexplore.exe";
                testExist = new File(returnString);
                if (! testExist.exists()) {
                    returnString = "C:\\Program Files\\Microsoft\\Internet Explorer\\Iexplore.exe";
                    testExist = new File(returnString);
                    if (! testExist.exists()) {
                        returnString = "C:\\Program Files\\Plus!\\Microsoft Internet\\Iexplore.exe";
                        testExist = new File(returnString);
                        if (! testExist.exists()) {
                            returnString = "C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE";
                        } else {
                            returnString = "start";
                        }
                    }
                }

                break;
            case OSType.LINUX: // Linux
                returnString = "/usr/bin/konqueror";
                testExist = new File(returnString);
                if (! testExist.exists()) {
                    returnString = "/usr/bin/mozilla";
                    testExist = new File(returnString);
                    if (! testExist.exists()) {
                        returnString = "/usr/bin/netscape";
                    } else {
                        returnString = "/usr/local/bin/mozilla";
                    }
                }
 
                break;
            case OSType.UNIX: // Unix variant
                returnString = "/usr/bin/konqueror";
                testExist = new File(returnString);
                if (! testExist.exists()) {
                    returnString = "/usr/bin/mozilla";
                    testExist = new File(returnString);
                    if (! testExist.exists()) {
                        returnString = "/usr/bin/netscape";
                    } else {
                        returnString = "/usr/local/bin/mozilla";
                    }
                }
                break;
            case OSType.MAC: // MAC
                returnString = "open";
                break;
            default: // UNKNOWN
                returnString = "/usr/bin/netscape";
                break;
        }

        logger.debug("getBrowserFile() return value=" + returnString);
        
        return returnString;
    }


    private String hasHandler(String externalLink) {
        String returnString = "";

        int lastDot = externalLink.lastIndexOf(".");
        if (lastDot != -1) {
            // get extension
            String ext = externalLink.substring(lastDot + 1, externalLink.length());
            ext = ext.toLowerCase();
            logger.info("hasHandler() extenion is: " + ext);
            int numHndlrs = handlerList.size();
            if (numHndlrs > 0) {
                Iterator it = handlerList.iterator();
                docTypeHandler dh;
                while (it.hasNext()) {
                    dh = (docTypeHandler) it.next();
                    if (dh.isCompat(ext)) {
                        returnString = dh.getApp();
                        break;
                    }
                }
            } // end for having handlers
            else {
                logger.info("hasHandler() NO EXTERNAL HANDLERS DEFINED!");
            }
        } // end for having an extension
        else {
            logger.info("hasHandler() NO EXTENSION FOUND!");
        }

        return returnString;
    }


    public void doExternal(String externalLink) {
        String lowerL = externalLink.toLowerCase();
        logger.info("doExternal() Loading externally: " + externalLink);
        if (externalLink.equals("home") || externalLink.equals("results")) {
            showMessage(Messages.getString("DocSearch.notExtrnlyVwble"), Messages.getString("DocSearch.ntExtVwblMsg"));
        }
        else {
            String app = hasHandler(externalLink);
            if (lowerL.startsWith("file:/")) { // remove "file:/"
                externalLink = externalLink.substring(6, externalLink.length());
            }
            if (externalLink.indexOf(" ") != -1) {
                if (lowerL.startsWith("http"))
                    externalLink = Utils.replaceAll(" ", externalLink, "%20");
                else {
                    switch (env.getOSType()) {
                        case OSType.WIN_32: // windows
                            externalLink = "\"" + externalLink + "\"";
                            break;
                        default: // unix
                            // externalLink = "'"+externalLink+"'";
                            break;
                        case OSType.LINUX: // linux
                            // externalLink = Utils.escapeSpaces(externalLink);
                            break;
                    } // end for switching os type
                } // end for space file doesn't start with http
            } // end for has a space
            if (app.equals("") || externalLink.toLowerCase().startsWith("http")) {
                app = defaultHndlr;
            }
            else {
                logger.info("doExternal() Using user specified handler: " + app);
            }
            if (app.indexOf(" ") != -1) {
                app = "\"" + app + "\"";
            }
            String execString = app + " " + externalLink;
            try {
                setStatus(execString);
                logger.info("doExternal() Executing runtime command:\n" + execString);
                if (env.getOSType() != 0) {
                    String[] cmdArray = new String[2];
                    cmdArray[0] = app;
                    cmdArray[1] = externalLink;
                    Runtime.getRuntime().exec(cmdArray);
                }
                else {
                    Runtime.getRuntime().exec(execString);
                }
            }
            catch (Exception eR) {
                showMessage(dsErr, "\n" + execString + "\n" + eR.toString());
            }
        } // end for not "home" or "results"
    } // end for doExternal


    private void doBookmark() {
        if ((curPage.equals("home")) || (curPage.equals("results"))) {
            showMessage(Messages.getString("DocSearch.notBookmarkable"), Messages.getString("DocSearch.saveResultsPlease"));
        }
        // end for not bookmarkable
        else {
            // obtain title - if there was one
            String nbt = getTitle();
            NewBookmarkDialog nbd = new NewBookmarkDialog(this, Messages.getString("DocSearch.bookmark"), true);
            nbd.setDesc(nbt);
            String toAdd = curPage;
            if ((toAdd.startsWith("file://")) && (!toAdd.startsWith("file:///"))) {
                toAdd = "file:///" + toAdd.substring(6, toAdd.length());
            }
            nbd.setBMLocation(toAdd);
            nbd.init();
            nbd.setVisible(true);
            if (nbd.isConfirmed()) {
                addNewBookmark(new SimpleBookmark(nbd.getBMLocation(), nbd.getDesc()));
            }
        }
    }


    private void doManageIndexes() {
        if (!indexes.isEmpty()) {
            int numIndexes = indexes.size();
            ManageIndexesDialog min = new ManageIndexesDialog(this, Messages.getString("DocSearch.idxProps"), true);
            min.init();
            min.setVisible(true);
            if (min.returnBool) {
                // proceed to make the changes
                ArrayList newIndex = new ArrayList();
                DocSearcherIndex di;
                for (int i = 0; i < numIndexes; i++) {
                    // set searched
                    if (!min.deletionSelected(i)) {
                        di = ((DocSearcherIndex) indexes.get(i));
                        di.setShouldBeSearched(min.searchSelected(i));
                        if (min.updateSelected(i))
                            idx.updateIndex(di);
                        if (min.exportSelected(i))
                            doExport(di);
                        newIndex.add(di);
                    } else {
                        // recursively delete the content
                        // in the selected index
                        di = ((DocSearcherIndex) indexes.get(i));
                        deleteRecursive(di.getIndexPath());
                    }
                    // end for deleting and index
                }
                indexes = newIndex;
            }
        } else
            showMessage(dsErr, Messages.getString("DocSearch.plsCrtNewIdx"));
    }


    private void deleteRecursive(String folderToDelete) {
        int curFoldNum = 0;
        File curFolderFile;
        String curFold = "";
        String[] subFolds;
        int numSubFolds = 0;
        int totalFolds = 0;
        int numFiles = 0;
        String curFolderString = "";
        String curFileString = "";
        File testFile;
        try {
            // first obtain a list of all folders
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
            ArrayList allFold = new ArrayList();
            allFold.add(folderToDelete);
            setStatus(dsRmvgIdxFis);
            do {
                // get list of sub folders
                curFolderString = (String) allFold.get(curFoldNum);
                curFolderFile = new File(curFolderString);
                subFolds = curFolderFile.list(ff);
                numSubFolds = subFolds.length;
                for (int y = 0; y < numSubFolds; y++) {
                    curFold = curFolderString + pathSep + subFolds[y] + pathSep;
                    curFold = Utils.replaceAll(pathSep + pathSep, curFold, pathSep);
                    allFold.add(curFold);
                    totalFolds++;
                }
                curFoldNum++;
            } while (curFoldNum < totalFolds);
            // next get a list of all files
            ArrayList allFiles = new ArrayList();
            Iterator foldIt = allFold.iterator();
            String[] filesString;
            while (foldIt.hasNext()) {
                curFolderString = (String) foldIt.next();
                curFolderFile = new File(curFolderString);
                // get the files
                filesString = curFolderFile.list();
                numFiles = filesString.length;
                for (int y = 0; y < numFiles; y++) {
                    // add the files
                    curFileString = curFolderString + pathSep + filesString[y];
                    curFileString = Utils.replaceAll(pathSep + pathSep, curFileString, pathSep);
                    testFile = new File(curFileString);
                    if (!testFile.isDirectory())
                        allFiles.add(curFileString);
                }
            }
            // end for iterating
            // delete all files
            Iterator fileIt = allFiles.iterator();
            while (fileIt.hasNext()) {
                curFileString = (String) fileIt.next();
                testFile = new File(curFileString);
                testFile.delete();
            }
            // end while deleteing
            // delete all folders
            int numFoldTotal = allFiles.size();
            for (int y = numFoldTotal - 1; y >= 0; y--) {
                curFolderString = (String) allFiles.get(y);
                curFolderFile = new File(curFolderString);
                logger.info("deleteRecursive() " + dsDeleting + " " + curFolderString);
                curFolderFile.delete();
            }
            // delete last folder
            curFolderFile = new File(folderToDelete);
            curFolderFile.delete();
        }
        // end for trrying recursive delete
        catch (Exception eR) {
            showMessage(dsErr, eR.toString());
        }
        finally {
            setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            setStatus(dsIdxRemoved);
        }
    }


    private void cb() {
        if (useAuthor.isSelected()) {
            authorField.setEnabled(true);
        } else {
            authorField.setEnabled(false);
        }

        if (useDate.isSelected()) {
            fromField.setEnabled(true);
            toField.setEnabled(true);
        } else {
            fromField.setEnabled(false);
            toField.setEnabled(false);
        }

        if (useSize.isSelected()) {
            sizeFromField.setEnabled(true);
            sizeToField.setEnabled(true);
        } else {
            sizeFromField.setEnabled(false);
            sizeToField.setEnabled(false);
        }

        if (useType.isSelected()) {
            fileType.setEnabled(true);
        } else {
            fileType.setEnabled(false);
        }
    }


    protected void doZipArchiveUpdate(DocSearcherIndex di) {
        // try and obtain meta data from the file
        // based on this new meta data see if we can obtain new index
        // fourth column
        String tempArchiveDir = Utils.getFolderOnly(di.getPath());
        String metaFileName = FileUtils.addFolder(tempArchiveDir, "archives.htm");
        String tempManifestFileName = FileUtils.addFolder(fEnv.getWorkingDirectory(), "temp_manifest.htm");
        boolean okToUpdate = true;
        if (metaFileName.toLowerCase().startsWith("http:")) {
            okToUpdate = downloadURLToFile(metaFileName, tempManifestFileName);
            metaFileName = tempManifestFileName;
        }
        if (okToUpdate) {
            // load the meta data
            try {
                Table tempTable = new Table(6, 100);
                tempTable.htmlLoad(metaFileName, "");
                String newIndexDate = di.getLastIndexed();
                okToUpdate = tempTable.loadOK;
                if (okToUpdate) {
                    // search for our new date
                    int numArchs = tempTable.colSize();
                    boolean foundArch = false;
                    int matchInt = 0;
                    for (int i = 0; i < numArchs; i++) {
                        if (tempTable.inItem(0, i).equals(di.getDescription())) {
                            matchInt = i;
                            foundArch = true;
                            break;
                        }
                    }
                    // end for iterating
                    if (foundArch) {
                        if (!tempTable.inItem(1, matchInt).equals(di.getLastIndexed())) {
                            newIndexDate = tempTable.inItem(1, matchInt);
                            String downloadFileName = FileUtils.addFolder(tempArchiveDir, tempTable.inItem(2, matchInt));
                            if (downloadFileName.toLowerCase().startsWith("http:")) {
                                String tempZipFileName = FileUtils.addFolder(fEnv.getWorkingDirectory(), "temp_zip_download.zip");
                                okToUpdate = downloadURLToFile(downloadFileName, tempZipFileName);
                                downloadFileName = tempZipFileName;
                            }
                            if (okToUpdate) {
                                // now delete recursively the directory
                                // and extract the new zip
                                setStatus(dsDeleting + " " + di.getIndexPath());
                                deleteRecursive(di.getIndexPath());
                                File newIndP = new File(di.getIndexPath());
                                boolean madeFold = newIndP.mkdir();
                                if (newIndP.exists())
                                    madeFold = true;
                                // boolean finalSuccess = true;
                                if (madeFold) {
                                    setStatus(dsUnZipn + " " + downloadFileName + " --> " + di.getIndexPath());
                                    UnZippHandler uz = new UnZippHandler(downloadFileName, di.getIndexPath());
                                    try {
                                        uz.unZip();
                                        setStatus(dsUnZipD);
                                        di.setLastIndexed(newIndexDate);
                                    } catch (Exception eZ) {
                                        // finalSuccess = false;
                                        showMessage(dsErr, eZ.toString());
                                    }
                                } else
                                    showMessage(Messages.getString("DocSearch.noMakeFolder"), di.getIndexPath());
                            }
                            // end if ok to update
                        }
                        // end if dates different
                        else
                            showMessage(Messages.getString("DocSearch.noUpdates"), Messages.getString("DocSearch.lastUpdateWas") + di.getLastIndexed());
                    }
                    // end if found arch
                    else
                        showMessage(Messages.getString("DocSearch.noMetaData"), Messages.getString("DocSearch.noMetaData") + " " + metaFileName);
                } else
                    showMessage(Messages.getString("DocSearch.noMetaData"), Messages.getString("DocSearch.noMetaData") + " " + metaFileName);
            }
            // end for trying to update Zip
            catch (Exception metaE) {
                setStatus(Messages.getString("DocSearch.noMetaData") + " " + metaFileName);
                okToUpdate = false;
            }
        }
    }


    private void doExport(DocSearcherIndex di) {
        // zip contents and place in archive Dir
        String archiveZipFileName = Utils.replaceAll(" ", di.getDescription(), "_");
        if (!archiveZipFileName.toLowerCase().endsWith(".zip")) {
            archiveZipFileName += ".zip";
        }
        String content = di.getPath();
        if (di.getIsWeb()) {
            content = di.getMatch();
        }
        String zipFileNameOnly = archiveZipFileName;
        archiveZipFileName = FileUtils.addFolder(di.getArchiveDir(), archiveZipFileName);
        ZippHandler zh = new ZippHandler(archiveZipFileName, di.getIndexPath());
        boolean zipSuccess = true;
        String errMsg = null;
        setStatus(Messages.getString("DocSearch.archIdx") + " " + di.getDescription() + " --> " + archiveZipFileName + ", " + plsWait);
        try {
            zh.zip();
        }
        catch (IOException ioe) {
            errMsg = ioe.toString();
            zipSuccess = false;
        }
        finally {
            setStatus(Messages.getString("DocSearch.archDone"));
        }
        
        if (zipSuccess) {
            showMessage(Messages.getString("DocSearch.archiveSuccess"), di.getDescription() + " " + Messages.getString("DocSearch.archivedFile") + archiveZipFileName);
        }
        else {
            showMessage(dsErr, errMsg);
        }

        // OK now update the archive table
        updateArchiveTable(di.getDescription(), di.getLastIndexed(), zipFileNameOnly, di.getArchiveDir(), content);
    }


    private void updateArchiveTable(String desc, String lastIndexed, String zipFileName, String archDir, String content) {
        boolean hasErr = false;
        String errMsg = "";
        try {
            String archivesFileName = FileUtils.addFolder(archDir, "archives.htm");
            setStatus(dsUpdtArchTbl + " " + archivesFileName);
            File textArchiveIndex = new File(archivesFileName);
            if (textArchiveIndex.exists()) {
                // read and update the file
                Table tempTable = new Table(6, 100);
                tempTable.htmlLoad(archivesFileName, "");
                tempTable.setCaption("DocSearcher Lucene Search Index Archive Listing");
                int numI = tempTable.colSize();
                String tempDesc = "";
                int foundAtNum = numI;
                // parse it
                for (int i = 1; i < numI; i++) {
                    tempDesc = tempTable.inItem(0, i);
                    if (tempDesc.equals(desc)) {
                        foundAtNum = i;
                        break;
                    }
                }
                // end for iterating
                //
                tempTable.add(desc, 0, foundAtNum);
                tempTable.add(lastIndexed, 1, foundAtNum);
                tempTable.add(zipFileName, 2, foundAtNum);
                tempTable.add(content, 3, foundAtNum);
                // save it
                int k = tempTable.colSize();
                int l = tempTable.rowSize();
                tempTable.fpSave(archivesFileName, k, l);
            } else {
                // create a new archive index
                Table tempTable = new Table(6, 102);
                tempTable.setCaption("DocSearcher Lucene Search Index Archive Listing");
                //
                // add the header
                tempTable.add("Description", 0, 0);
                tempTable.add("Date of Indexing", 1, 0);
                tempTable.add("Archive Zip File", 2, 0);
                tempTable.add("Directory or Content", 3, 0);
                // add the data
                tempTable.add(desc, 0, 1);
                tempTable.add(lastIndexed, 1, 1);
                tempTable.add(zipFileName, 2, 1);
                tempTable.add(content, 3, 1);
                // save it
                int k = tempTable.colSize();
                int l = tempTable.rowSize();
                tempTable.fpSave(archivesFileName, k, l);
            }
        }
        // end for try
        catch (Exception eT) {
            hasErr = true;
            errMsg = eT.toString();
        }
        if (hasErr)
            showMessage(dsErr, errMsg);
        else
            setStatus(dsArchTblUpdtd);
    }


    private boolean downloadURLToFile(String urlString, String fileToSaveAs) {
        byte curBint;
        boolean returnBool = true;
        int numBytes = 0;
        int curI = 0;
        FileOutputStream dos;
        InputStream urlStream;
        int lastPercent = 0;
        int curPercent = 0;
        try {
            URL url = new URL(urlString);
            File saveFile = new File(fileToSaveAs);
            dos = new FileOutputStream(saveFile);
            URLConnection conn = url.openConnection();
            conn.setDoInput(true);
            conn.setUseCaches(false);
            conn.connect();
            urlStream = conn.getInputStream();
            int totalSize = conn.getContentLength();
            while (curI != -1) {
                curI = urlStream.read();
                curBint = (byte) curI;
                if (curI == -1) {
                    break;
                }
                dos.write(curBint);
                numBytes++;
                if (totalSize > 0) {
                    curPercent = (numBytes * 100) / totalSize;
                    if (curPercent != lastPercent) {
                        setStatus(curPercent + " " + dsPcntDnld + " " + dsOfFile + " " + urlString + " " + dsBytsTot + " " + totalSize);
                        lastPercent = curPercent;
                    }
                }
                // end if total size not zero
            }
            urlStream.close();
            dos.close();
        } catch (Exception e) {
            logger.fatal("downloadURLToFile() failed", e);
            showMessage(dsDnLdErr, e.toString());
            returnBool = false;
        }

        return returnBool;
    }


    private void doImport(String zipFileString, String description, String dateIndexed, boolean searchedByDefault, boolean isWeb, int indexPolicy) {
        // may be just a URL
        boolean successFulDownload = true;
        if (dateIndexed.equals("")) {
            dateIndexed = DateTimeUtils.getToday();
        }
        //
        boolean zipSuccess = true;
        String errMsg = "";
        String indexFolderName = Utils.replaceAll(" ", description, "_");
        String loadString = zipFileString;
        if (loadString.toLowerCase().startsWith("http://")) {
            // download zip and load the downloaded zip file
            String nameOnlyStr = Utils.getNameOnly(loadString);
            loadString = FileUtils.addFolder(fEnv.getArchiveDirectory(), nameOnlyStr);
            successFulDownload = downloadURLToFile(zipFileString, loadString);
            if (!successFulDownload) {
                errMsg = dsDnLdErr + " " + zipFileString;
                zipSuccess = false;
            }
        }
        // end for downloading the zip
        indexFolderName = FileUtils.addFolder(fEnv.getIndexDirectory(), indexFolderName);
        File newIndexFolder = new File(indexFolderName);
        boolean dirMade = newIndexFolder.mkdir();
        if (newIndexFolder.exists()) {
            setStatus(dsErr + " : " + FOLDER_ALREADY_EXISTS + "--> " + indexFolderName);
            dirMade = true;
        }
        if ((dirMade) && (successFulDownload)) {
            UnZippHandler uz = new UnZippHandler(loadString, indexFolderName);
            setStatus(dsImptg + " " + description + " " + plsWait);
            try {
                uz.unZip();
                // add it in there
                DocSearcherIndex di = new DocSearcherIndex(zipFileString, description, searchedByDefault, 0, indexFolderName, isWeb, "", "", indexPolicy, fEnv.getArchiveDirectory());
                indexes.add(di);
            } catch (Exception eZ) {
                errMsg = eZ.toString();
                zipSuccess = false;
            } finally {
                setStatus(dsImprtDn);
            }
            if (zipSuccess) {
                showMessage(dsImprtSuccess, description + " " + dsWasImprtd);
            } else {
                showMessage(dsErrImptg + " : " + description, errMsg);
            }
        } else
            showMessage(dsErrImptg, Messages.getString("DocSearch.noMakeFolder") + "  " + indexFolderName);
    }


    private void getImportInfo() {
        ImportDialog id = new ImportDialog(this, Messages.getString("DocSearch.imprtIdx"), true);
        id.init();
        id.setVisible(true);
        if (id.getConfirmed()) {
            String importZipFileName = id.getUrlOrFileText().trim();
            String importFolderOnly = Utils.getFolderOnly(importZipFileName);
            String importManifestName = FileUtils.addFolder(importFolderOnly, "archives.htm");
            String zipArchNameOnly = Utils.getNameOnly(importZipFileName);
            boolean foundManifest = false;
            boolean foundManifestData = false;
            boolean doImport = true;
            //
            String zipFileString = importZipFileName;
            String description = "Unknown";
            String dateIndexed = "";
            boolean searchedByDefault = true;
            boolean isWeb = true;
            int indexPolicy = 0;
            //
            if (importManifestName.toLowerCase().startsWith("http:")) {
                // convert URL to file
                String tempManifestFileName = FileUtils.addFolder(fEnv.getWorkingDirectory(), "temp_manifest.htm");
                foundManifest = downloadURLToFile(importManifestName, tempManifestFileName);
                if (foundManifest) {
                    importManifestName = tempManifestFileName;
                }
            }
            // end for manifest
            else {
                File testManifestFile = new File(importManifestName);
                if (testManifestFile.exists()) {
                    foundManifest = true;
                }
            }
            // end for not a URL
            if (foundManifest) {
                // try and retrieve the manifest data
                Table tempTable = new Table(11, 100);
                tempTable.htmlLoad(importManifestName, "");
                int numI = tempTable.colSize();
                // int tempSbd = 0;
                String tempArchFile = "";
                String tempDesc = "";
                String tempDateIndexed = "";
                // parse it
                for (int i = 1; i < numI; i++) {
                    //
                    try {
                        tempDesc = tempTable.inItem(0, i);
                        tempArchFile = tempTable.inItem(2, i);
                        tempDateIndexed = tempTable.inItem(1, i);
                        if (zipArchNameOnly.equals(tempArchFile)) {
                            description = tempDesc;
                            dateIndexed = tempDateIndexed;
                            foundManifestData = true;
                            setStatus(dsArchDescFnd + description);
                            break;
                        }
                        else {
                            logger.info("getImportInfo() " + zipArchNameOnly + " != " + tempArchFile);
                        }
                    }
                    catch (Exception eR) {
                        setStatus(dsErrParseMnfst + " " + eR.toString());
                    }
                }
                // end for iterating over manifest file entries
            }

            if (!foundManifestData) {
                // show a dialog to obtain archive meta data
                // IF dialog is cancelled ; doImport = false
                ManifestDialog md = new ManifestDialog(this, Messages.getString("DocSearch.importIdxProperties"), true);
                md.init();
                md.setVisible(true);
                if (md.getConfirmed()) {
                    description = md.getDescFieldText().trim();
                    dateIndexed = DateTimeUtils.getToday();
                    isWeb = md.webBoxSelected();
                    searchedByDefault = md.sbdBoxSelected();
                    indexPolicy = md.indexFreqIdx();
                }
                else {
                    doImport = false;
                }
            }

            if (doImport) {
                // create our new index!
                doImport(zipFileString, description, dateIndexed, searchedByDefault, isWeb, indexPolicy);
            }
        }
        // end for confirmed
    }


    private void doCommand(String commandString, String indexString) {
        boolean doSndMail = sendNoticeOnIdxingChanges();
        boolean isTxtFormt = isTextEmailFormat();
        logger.debug("doCommand() " + Messages.getString("DocSearch.cmd") + commandString + Messages.getString("DocSearch.idx") + indexString);
        if (commandString.equals(Messages.getString("DocSearch.listCMD"))) {
            int numIndexes = indexes.size();
            if (numIndexes > 0) {
                DocSearcherIndex di;
                Iterator it = indexes.iterator();
                int countNum = 1;
                while (it.hasNext()) {
                    di = (DocSearcherIndex) it.next();
                    logger.info("doCommand() " + countNum + ". " + di.getDescription());
                    countNum++;
                }
            }
            else {
                logger.warn("doCommand() " + Messages.getString("DocSearch.noIndexFound"));
            }
        }
        else if (commandString.equals(Messages.getString("DocSearch.updateCMD"))) {
            if (indexString.trim().equals("")) {
                logger.info("doCommand() " + Messages.getString("DocSearch.pleaseSpecifyAnIndex"));
            }
            else {
                int numIndexes = indexes.size();
                boolean foundMatch = false;
                if (numIndexes > 0) {
                    DocSearcherIndex di;
                    boolean sendAMess = sendNoticeOnIdxingChanges();
                    Iterator it = indexes.iterator();
                    while (it.hasNext()) {
                        di = (DocSearcherIndex) it.next();
                        if (di.getDescription().equals(indexString)) {
                            idx.setDoEmail(sendAMess);
                            idx.setEmailText(isTextEmailFormat());
                            idx.updateIndex(di);
                            if ((sendAMess) && (idx.getTotalChanges() > 0)) {
                                sendEmail(di.getDescription() + " " + dsUpdts, idx.getUpDateNotes());
                            }
                            foundMatch = true;
                            break;
                        }
                    }
                    // end for match
                    if (! foundMatch) {
                        logger.warn("doCommand() " + indexString + Messages.getString("DocSearch.noMatchesFound"));
                    }
                }
                else {
                    logger.warn("doCommand() " + Messages.getString("DocSearch.noIndexFound"));
                }
            }
            // end for we have an index
        }
        // end for update
        else if (commandString.equals(Messages.getString("DocSearch.exportCMD"))) {
            if (indexString.trim().equals("")) {
                logger.info("doCommand() " + Messages.getString("DocSearch.pleaseSpecifyAnIndex"));
            }
            else {
                int numIndexes = indexes.size();
                boolean foundMatch = false;
                if (numIndexes > 0) {
                    DocSearcherIndex di;
                    Iterator it = indexes.iterator();
                    while (it.hasNext()) {
                        di = (DocSearcherIndex) it.next();
                        if (di.getDescription().equals(indexString)) {
                            doExport(di);
                            foundMatch = true;
                            break;
                        }
                    }
                    // end for match
                    if (! foundMatch) {
                        logger.warn("doCommand()" + indexString + Messages.getString("DocSearch.noMatchesFound"));
                    }
                }
                else {
                    logger.warn("doCommand() " + Messages.getString("DocSearch.noIndexFound"));
                }
            }
            // end for we have an index
        }
        else if (commandString.startsWith(Messages.getString("DocSearch.searchCMD"))) {
            String searchT = commandString.substring(7, commandString.length());
            setStatus(Messages.getString("DocSearch.searchingFor") + searchT + "...");
            if (indexString.trim().equals("")) {
                doSearch(searchT);
            }
            else {
                int numIndexes = indexes.size();
                if (numIndexes > 0) {
                    DocSearcherIndex di;
                    boolean foundMatch = false;
                    Iterator it = indexes.iterator();
                    while (it.hasNext()) {
                        di = (DocSearcherIndex) it.next();
                        if (di.getDescription().equals(indexString)) {
                            di.setShouldBeSearched(true);
                            foundMatch = true;
                        }
                        else {
                            di.setShouldBeSearched(false);
                        }
                    }
                    // end for match

                    if (! foundMatch) {
                        logger.warn("doCommand() " + indexString + Messages.getString("DocSearch.indexNotFound"));
                    }
                    else {
                        doSearch(searchT);
                    }
                }
                else {
                    logger.warn("doCommand() " + Messages.getString("DocSearch.noIndexFound"));
                }
            }

            // proceed to do search
        }
        else if (commandString.equals("analyze_log")) {
            try {
                LogAnalysis.doLogAnalysis(this, indexString);
            }
            catch (Exception eF) {
                logger.warn("doCommand() " + Messages.getString("DocSearch.errAnalyzingLogFile") + indexString + "\n" + eF.toString());
            }
        }
        else if (commandString.equals(Messages.getString("DocSearch.importLower"))) {
            ArchiveMetaData amd = new ArchiveMetaData(indexString);
            //
            doImport(indexString, amd.getDesc(), amd.getDI(), amd.getSDB(), amd.getIsWeb(), amd.getIndexPolicy());
            // System.out.println("\nIMPORT index -->"+indexString);
            // System.out.println("\ndescription -->"+amd.getDesc());
        } // end for importing index
        else {
            logger.info("doCommand() " + Messages.getString("DocSearch.cmdUsage")); // list
        }
        // the command line help

        doExit();
    }


    private void getSeachLogReport() {
        JFileChooser fdo = new JFileChooser();
        fdo.setCurrentDirectory(new File(fEnv.getWorkingDirectory()));
        int fileGotten = fdo.showDialog(this, Messages.getString("DocSearch.select"));
        if (fileGotten == JFileChooser.APPROVE_OPTION) {
            File file = fdo.getSelectedFile();
            try {
                LogAnalysis.doLogAnalysis(this, file.toString());
            } catch (Exception eF) {
                setStatus(Messages.getString("DocSearch.statusLogError") + eF.toString());
            }
        }
    }


    private void doMetaReport() {
        MetaReport mr = new MetaReport();
        mr.getMetaReport(this);
    }

    class Hyperactive implements HyperlinkListener {
        /**
         * Log4J
         */
        private Logger logger = Logger.getLogger(getClass().getName()); 

        public void hyperlinkUpdate(HyperlinkEvent e) {
            if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
                // JEditorPane pane = (JEditorPane)e.getSource();
                if (e instanceof HTMLFrameHyperlinkEvent) {
                    String urlString = e.getURL().toString();
                    doExternal(urlString);

                }
                else {
                    try {
                        String urlString = e.getURL().toString();
                        if ((urlString.toLowerCase().endsWith(".exe")) || (urlString.toLowerCase().endsWith(".sh"))) {
                            try {
                                if (urlString.startsWith("file:/")) {
                                    urlString = urlString.substring(6, urlString.length());
                                }
                                Runtime.getRuntime().exec(urlString);
                            } catch (Exception eR) {
                                setStatus(urlString + " : " + eR.toString());
                                eR.printStackTrace();
                            }
                        } else {
                            if (loadExternal) {
                                doExternal(urlString);
                            }
                            else {
                                setPage(urlString);
                            }
                        }
                    }
                    catch (Throwable t) {
                        logger.fatal("hyperLinkUpdate() failed", t);
                        showMessage(errLoadPage, errReported + t.toString());
                    }
                }
            }
        }
    }

    class ComboListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            if (e != null) {
                if (e.getSource() != null) {
                    if (e.getSource() == searchField) {
                        // String source = e.getActionCommand();
                        String act = "";
                        if (searchField.getSelectedItem() != null) {
                            act = e.getActionCommand();
                            if (act != null) {
                                if (act.equals("comboBoxEdited")) {
                                    doThreadedSearch();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    class CheckBoxListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            // String source = e.getActionCommand();
            cb();
        }
    }


    private void doHandlers() {
        DsProperties hd = new DsProperties(this, "Options", true);
        hd.init();
        hd.setVisible(true);
        if (hd.getConfirmed()) {
            String tempLafChosen = "";
            // check everything
            switch (hd.getReturnInt()) {
                default: // nothing
                    break;
                case 0: // default hdnler
                    defaultHndlr = hd.defltHndlrText();
                    break;
                case 1: // look and feel
                    tempLafChosen = hd.lafSelected();
                    if (!tempLafChosen.equals(""))
                        lafChosen = tempLafChosen;
                    try {
                        UIManager.setLookAndFeel(lafChosen);
                        SwingUtilities.updateComponentTreeUI(this);
                        setSize(new Dimension(kDefaultX, kDefaultY));
                    } catch (Exception eN) {
                        showMessage(dsErr, eN.toString());
                    }
                    // now for max file size to index
                    long newMFSI = 0;
                    try {
                        newMFSI = Long.parseLong(hd.maxSizeField());
                        if (newMFSI > 0) {
                            newMFSI = newMFSI * 1024;
                        }
                        setMaxFileSize(newMFSI);
                    }
                    catch (Exception nfe) {
                        logger.error("doHandler() failed", nfe);
                        showMessage(dsErr, nfe.toString());
                    }
                    // now for max hits to show
                    String newMaxInt = hd.maxFieldText().trim();
                    if (! newMaxInt.equals("")) {
                        try {
                            int newMaxN = Integer.parseInt(newMaxInt);
                            if ((newMaxN > 0) && (newMaxN < 1000)) {
                                maxNumHitsShown = newMaxN;
                            }
                        }
                        catch (NumberFormatException nfe) {
                            logger.error("doHandler() failed", nfe);
                            showMessage(dsErr, nfe.toString());
                        }
                    }
                    if (hd.loadExternalSelected()) {
                        loadExternal = true;
                    }
                    else {
                        loadExternal = false;
                    }
                    break;
                case 2: // index directory
                    //
                    String newIndexDir = hd.getDsDirFieldText().trim();
                    if (!newIndexDir.equals("")) {
                        // copy over our files
                        if (hd.copyDirFilesSelected()) {
                            // including our index list file
                            copyFiles(fEnv.getIndexDirectory(), newIndexDir);
                            // change the file settings on the DsIndex objects
                            Iterator iterator = indexes.iterator();
                            DocSearcherIndex curI;
                            String curIdxrStr = "";
                            while (iterator.hasNext()) {
                                curI = (DocSearcherIndex) iterator.next();
                                curIdxrStr = curI.getIndexPath();
                                if (curIdxrStr.startsWith(fEnv.getIndexDirectory())) {
                                    curI.setIndexPath(newIndexDir + curIdxrStr.substring(fEnv.getIndexDirectory().length(), curIdxrStr.length()));
                                }
                            }
                            setStatus(FINISHED_COPYING);
                        }
                        fEnv.setIndexDirectory(newIndexDir);
                    }
                    String newDirFieldTExt = hd.getTmpFieldText().trim();
                    //
                    if (!newDirFieldTExt.equals(""))
                        resetTempDir(newDirFieldTExt);
                    // 
                    String newWorkingDirFieldTExt = hd.workingDirFieldText().trim();
                    if (!newWorkingDirFieldTExt.equals(""))
                        resetWorkingDir(newWorkingDirFieldTExt);
                    break;
                case 3: // email stuff
                    gateway = hd.getGateWayFieldText();
                    gatewayPwd = hd.gatewayPwdFieldText();
                    gatewayUser = hd.gatewayUserFieldText();
                    if (hd.sendEmailBxSelected())
                        sendEmailNotice = "true";
                    else
                        sendEmailNotice = "true";
                    if (hd.textRBSelected())
                        emailFormat = hd.TEXT_FORMAT;
                    else
                        emailFormat = hd.HTML_FORMAT;
                    break;
            }
        }
    } // end for doing handlers


    private void getHandlers() {
        docTypeHandler dh;
        // pdf
        switch (env.getOSType()) {
            case OSType.WIN_32: // windows
                break;
            case OSType.LINUX: // linux
                if (FileUtils.fileExists("/usr/bin/xpdf")) {
                    dh = new docTypeHandler("pdf", "Portable Document Format", "/usr/bin/xpdf");
                    handlerList.add(dh);
                } else if (FileUtils.fileExists("/usr/bin/kghostview")) {
                    dh = new docTypeHandler("pdf", "Portable Document Format", "/usr/bin/kghostview");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/oowriter")) {
                    dh = new docTypeHandler("sxw", "Star Office  or Open Office Writer", "/usr/bin/oowriter");
                    handlerList.add(dh);
                    dh = new docTypeHandler("doc", "Microsoft Word Document", "/usr/bin/oowriter");
                    handlerList.add(dh);
                    dh = new docTypeHandler("rtf", "Rich Text Format Document", "/usr/bin/oowriter");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/oocalc")) {
                    dh = new docTypeHandler("sxc", "Star Office  or Open Office Calc", "/usr/bin/oocalc");
                    handlerList.add(dh);
                    dh = new docTypeHandler("xls", "Microsoft Excell Spreadsheet", "/usr/bin/oocalc");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/ooimpress")) {
                    dh = new docTypeHandler("sxi", "Star Office  or Open Office Impress", "/usr/bin/ooimpress");
                    handlerList.add(dh);
                    dh = new docTypeHandler("ppt", "Microsoft Powerpoint Presentation", "/usr/bin/ooimpress");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/kate")) {
                    dh = new docTypeHandler("txt", "Text File", "/usr/bin/kate");
                    handlerList.add(dh);
                    dh = new docTypeHandler("java", "Java Source Code", "/usr/bin/kate");
                    handlerList.add(dh);
                }
                else if (FileUtils.fileExists("/usr/bin/gedit")) {
                    dh = new docTypeHandler("txt", "Text File", "/usr/bin/gedit");
                    handlerList.add(dh);
                    dh = new docTypeHandler("java", "Java Source Code", "/usr/bin/gedit");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/konqueror")) {
                    dh = new docTypeHandler("htm", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                    dh = new docTypeHandler("html", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jsp", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                    dh = new docTypeHandler("asp", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                    dh = new docTypeHandler("cfm", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                    dh = new docTypeHandler("shtml", "Web Page", "/usr/bin/konqueror");
                    handlerList.add(dh);
                }
                else if (FileUtils.fileExists("/usr/bin/quanta")) {
                    dh = new docTypeHandler("htm", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                    dh = new docTypeHandler("html", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jsp", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                    dh = new docTypeHandler("asp", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                    dh = new docTypeHandler("cfm", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                    dh = new docTypeHandler("shtml", "Web Page", "/usr/bin/quanta");
                    handlerList.add(dh);
                }
                else if (FileUtils.fileExists("/usr/bin/mozilla")) {
                    dh = new docTypeHandler("htm", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                    dh = new docTypeHandler("html", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jsp", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                    dh = new docTypeHandler("asp", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                    dh = new docTypeHandler("cfm", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                    dh = new docTypeHandler("shtml", "Web Page", "/usr/bin/mozilla");
                    handlerList.add(dh);
                }
                else if (FileUtils.fileExists("/usr/bin/galeon")) {
                    dh = new docTypeHandler("htm", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                    dh = new docTypeHandler("html", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jsp", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                    dh = new docTypeHandler("asp", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                    dh = new docTypeHandler("cfm", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                    dh = new docTypeHandler("shtml", "Web Page", "/usr/bin/galeon");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/ark")) {
                    dh = new docTypeHandler("zip", "Zip Archive", "/usr/bin/ark");
                    handlerList.add(dh);
                }
                if (FileUtils.fileExists("/usr/bin/kpaint")) {
                    dh = new docTypeHandler("png", "Portable Network Graphics", "/usr/bin/kpaint");
                    handlerList.add(dh);
                    dh = new docTypeHandler("gif", "GIF Graphics", "/usr/bin/kpaint");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jpg", "JPG Graphics", "/usr/bin/kpaint");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jpeg", "JPEG Graphics", "/usr/bin/kpaint");
                    handlerList.add(dh);
                }
                else if (FileUtils.fileExists("/usr/bin/gimp")) {
                    dh = new docTypeHandler("png", "Portable Network Graphics", "/usr/bin/gimp");
                    handlerList.add(dh);
                    dh = new docTypeHandler("gif", "GIF Graphics", "/usr/bin/gimp");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jpg", "JPG Graphics", "/usr/bin/gimp");
                    handlerList.add(dh);
                    dh = new docTypeHandler("jpeg", "JPEG Graphics", "/usr/bin/gimp");
                    handlerList.add(dh);
                }
                break;
            case OSType.UNIX: // unix
                break;
            case OSType.MAC: // mac
                break;
        } // end for looking at os
    }


    private void doObjectLoad(int loadInt, String fileName) {
        // loadInt 0= broken links, 1= image descriptions, 2= allpages cache
        String endRow = "</tr";
        String endCell = "</td";
        // String startRow="<tr";
        String startCell = "<td";
        // boolean inCell=false;
        boolean inTag = false;
        StringBuffer tagBuf = new StringBuffer();
        StringBuffer textBuf = new StringBuffer();
        File loadFile = new File(fileName);
        String lowerTag = "";
        String tag = "";
        int curCell = 0;
        String[] cells;
        int numCells = 0;
        int numRowsForObject = Utils.getNumObjectRows(fileName);
        if (numRowsForObject > 0) {
            switch (loadInt) {
                case 0: // file handlers
                    docTypeHandler bi;
                    numCells = 3;
                    cells = new String[numCells];
                    for (int i = 0; i < numCells; i++)
                        cells[i] = "";
                    // load and parse the file
                    try {
                        FileInputStream fi = new FileInputStream(loadFile);
                        int curI = 0; // reset i
                        char curChar = ' ';
                        while (curI != -1) {
                            curI = fi.read();
                            if (curI != -1) {
                                curChar = (char) curI;
                                if (curChar == '<') {
                                    // beginning of a tag
                                    inTag = true;
                                } else if (curChar == '>') {
                                    // end of a tag
                                    tagBuf.append(curChar);
                                    tag = tagBuf.toString();
                                    lowerTag = tag.toLowerCase();
                                    if (lowerTag.startsWith(endCell)) {
                                        cells[curCell] = textBuf.toString();
                                        textBuf = new StringBuffer();
                                        curCell++;
                                    } // end of a cell
                                    else if (lowerTag.startsWith(endRow)) {
                                        curCell = 0;
                                        bi = new docTypeHandler(cells[0], cells[1], cells[2]);
                                        handlerList.add(bi);
                                    } // end of a row
                                    else if (lowerTag.startsWith(startCell)) {
                                        textBuf = new StringBuffer();
                                    } // end of startRow
                                    // always reset buffer
                                    inTag = false;
                                    tagBuf = new StringBuffer();
                                } // end for end of a tag
                                if (inTag)
                                    tagBuf.append(curChar);
                                else if (curChar != '>')
                                    textBuf.append(curChar);
                            } else
                                break;
                        } // end while reading file
                        fi.close();
                    }
                    catch (Exception e) {
                        logger.fatal("onObjectLoad() error loading from:" + fileName, e);
                    }
                    break;
            } // end for switching loading
        } // file exists and we have rows
        else {
            logger.info("onObjectLoad() Nothing found: " + fileName);
        }
    } // end for doIbjectLoad


    public ArrayList getLafs() {
        ArrayList lafList = new ArrayList();
        Object[] objs = UIManager.getInstalledLookAndFeels();
        UIManager.LookAndFeelInfo li;
        int numLafs = objs.length;
        for (int i = 0; i < numLafs; i++) {
            li = (UIManager.LookAndFeelInfo) objs[i];
            lafList.add(li.getClassName());
            // System.out.println(li.toString());
        }
        return lafList;
    } // end for getting LAFs


    /**
     * Copy files
     *
     * @param sourceFolder
     * @param destinationFolder
     */
    private void copyFiles(String sourceFolder, String destinationFolder) {
        if (logger.isDebugEnabled()) {
            logger.debug("copyFiles('" + sourceFolder + "', '" + destinationFolder + "') entered");
        }

        String stat = Messages.getString("DocSearch.copyingFolder") + " " + Utils.concatStr(sourceFolder);

        if (isLoading) {
            curStatusString = stat;
        }
        else {
            setStatus(stat);
        }

        // copy all content from sourceFolder to desctinationFolder
        File sourceFolderFile = new File(sourceFolder);
        File destinationFolderFile = new File(destinationFolder);
        if (sourceFolderFile.isDirectory() && destinationFolderFile.isDirectory()) {

            String allFilesList[] = sourceFolderFile.list();
            int numFiles = allFilesList.length;

            for (int i = 0; i < numFiles; i++) {
                String origFiNa = FileUtils.addFolder(sourceFolder, allFilesList[i]);
                String newNiNa = FileUtils.addFolder(destinationFolder, allFilesList[i]);

                File testDirFi = new File(origFiNa);
                if (testDirFi.isDirectory()) {
                    File newSubFile = new File(newNiNa);
                    if (newSubFile.mkdir()) {
                        copyFiles(origFiNa, newNiNa);
                    }
                    else {
                        setStatus(ERROR_CREATING_FOLDER + " " + newNiNa);
                    }
                }
                else {
                    copyFile(origFiNa, newNiNa);
                }
            }
        }
    }


    /**
     * Copy file
     *
     * @param originalFileName
     * @param newFileName
     */
    private void copyFile(String originalFileName, String newFileName) {
        if (logger.isDebugEnabled()) {
            logger.debug("copyFile('" + originalFileName + "', '" + newFileName + "') entered");
        }

        setStatus(plsWait + " " + COPYING_FILE + " " + Utils.concatStr(originalFileName) + " --> " + Utils.concatStr(newFileName));
            
        if (FileUtils.copyFile(originalFileName, newFileName)) {
            setStatus(FINISHED_COPYING + " " + Utils.concatStr(originalFileName));        
        }
        else {
            setStatus(dsErr + " : " + Utils.concatStr(originalFileName));
        }
    }


    /**
     * Method checks CDROM directory
     */
    private void checkCDROMDir() {
        String changeStr = "";
        boolean changeCD = false;
        String startDir = fEnv.getStartDirectory();
        
        if (isCDSearchTool) {
            // look at startDir
            switch (env.getOSType()) {
                case OSType.WIN_32: {
                    changeStr = startDir.substring(0, 2);
                    changeCD = true;
                    break;
                }
                case OSType.LINUX: {
                    // do nothing
                    if (startDir.indexOf("/mnt/cdrom1") != -1) {
                        changeStr = "/mnt/cdrom1";
                        changeCD = true;
                    }
                    else if (startDir.indexOf("/mnt/cdrom2") != -1) {
                        changeStr = "/mnt/cdrom2";
                        changeCD = true;
                    }
                    break;
                }
                case OSType.UNIX: {
                    break;
                }
                case OSType.MAC: {
                    break;
                }
            }
        }

        if (changeCD) {
            env.setCDROMDir(changeStr);
            logger.info("checkCDROMDir() new CDROM dir is: " + changeStr);
        }
    }


    /**
     * Gets CDROM path
     *
     * @param pathToChange
     * @return
     */
    private String getCDROMPath(String pathToChange) {
        // System.out.println("ORIG PATH: "+pathToChange);
        String ptc = pathToChange.substring(7, pathToChange.length());
        if ((ptc.startsWith("/")) || (ptc.startsWith("\\"))) {
            ptc = ptc.substring(1, ptc.length());
        }

        String tmpGetCDROMDr = env.getCDROMDir(); 
        if (! Utils.endsWithSlash(tmpGetCDROMDr)) {
            return tmpGetCDROMDr + "/" + ptc;
        }
        else {
            return tmpGetCDROMDr + ptc;
        }
    }


    private boolean isThisOnACd(String cdRomIdxList) {
        //
        // looks for startDir/cdrom_indexes
        // 
        File testCDFi = new File(cdRomIdxList);
        if (testCDFi.exists())
            return true;
        else
            return false;
    }


    /**
     * Load settings
     *
     * TODO load this with Properties mechanism!
     */
    private void loadSettings() {
        // loads prefs stored in savePrefsFiNa
        String prefsText = loadFile(fEnv.getUserPreferencesFile()).toString();

        // sendEmailNotice
        String sendEmailNoticeLoaded = Utils.getLineParam("sendEmailNotice", prefsText);
        if (! sendEmailNoticeLoaded.equals("")) {
            sendEmailNotice = sendEmailNoticeLoaded;
        }
        
        // numAdminEmails
        int adminEmNo = 0;
        String aen = Utils.getLineParam("numAdminEmails", prefsText);
        try {
            adminEmNo = Integer.parseInt(aen);
        } catch (Exception e) {
            logger.error("loadPrefs() failure with numAdminEmails", e);
            adminEmNo = 0;
        }
        if (adminEmNo > 0) {
            // add to arraylist of emails
            String curE = "";
            for (int i = 0; i < adminEmNo; i++) {
                curE = Utils.getLineParam("email" + i, prefsText);
                addEmail(curE);
            }
        }

        // maxFileSizeToIndex
        String newMaxFISI = Utils.getLineParam("maxFileSizeToIndex", prefsText);
        long newMaxFiSiInt = 0;
        if (! newMaxFISI.equals("")) {
            try {
                newMaxFiSiInt = Long.parseLong(newMaxFISI);
                setMaxFileSize(newMaxFiSiInt);
                logger.info("loadPref() max file size to index: " + newMaxFiSiInt);
            } catch (Exception e) {
                logger.error("loadPrefs() failure with newMaxFISI", e);
            }
        } else {
            logger.info("loadPrefs() no prefs for max file size found, using default: " + getMaxFileSize());
        }

        // emailFormat
        String emailFormatLoaded = Utils.getLineParam("emailFormat", prefsText);
        if (! emailFormatLoaded.equals("")) {
            emailFormat = emailFormatLoaded;
        }

        // gatewayUser
        String gatewayUserLoaded = Utils.getLineParam("gatewayUser", prefsText);
        if (! gatewayUserLoaded.equals("")) {
            gatewayUser = gatewayUserLoaded;
        }

        // loadExternal
        String loadExternalLoaded = Utils.getLineParam("loadExternal", prefsText);
        if (loadExternalLoaded.equals("false")) {
            loadExternal = false;
        } else {
            loadExternal = true;
        }

        // gatewayPWD 
        String gatewayPwdLoaded = Utils.getLineParam("gatewayPwd", prefsText);
        if (! gatewayPwdLoaded.equals("")) {
            gatewayPwd = gatewayPwdLoaded;
        }

        // gateway
        String gatewayLoaded = Utils.getLineParam("gateway", prefsText);
        if (! gatewayLoaded.equals("")) {
            gateway = gatewayLoaded;
        }

        // browser
        String browserLoaded = Utils.getLineParam("browser", prefsText);
        // TODO if browser empty, try to get from system with method getBrowserFile()
        if (! browserLoaded.equals("")) {
            defaultHndlr = browserLoaded;
        }

        // maxNumHitsShown
        String maxNumHitsShownLoaded = Utils.getLineParam("maxNumHitsShown", prefsText);
        if (! maxNumHitsShownLoaded.equals("")) {
            try {
                maxNumHitsShown = Integer.parseInt(maxNumHitsShownLoaded);
            } catch (Exception e) {
                logger.error("loadPrefs() failure with maxNumHitsShown", e);
                maxNumHitsShown = 250;
            }
        }

        // tempDir
        String tempDirLoaded = Utils.getLineParam("tempDir", prefsText);
        if (! tempDirLoaded.equals("")) {
            resetTempDir(tempDirLoaded);
        }

        // laf
        String lafLoaded = Utils.getLineParam("laf", prefsText);
        if (! lafLoaded.equals("")) {
            lafChosen = lafLoaded;
            if (env.isGUIMode()) {
                try {
                    UIManager.setLookAndFeel(lafChosen);
                    SwingUtilities.updateComponentTreeUI(this);
                    pack();
                } catch (Exception e) {
                    logger.error("loadPrefs() failure with laf", e);
                    setStatus(ERROR + " : " + e.toString());
                }
            }
        }

        // indexDir
        String indexDirLoaded = Utils.getLineParam("indexDir", prefsText);
        if (! indexDirLoaded.equals("")) {
            File testIdxDir = new File(indexDirLoaded);
            if (testIdxDir.exists()) {
                fEnv.setIndexDirectory(indexDirLoaded);
            }
            else {
                logger.info("loadPrefs() index dir doesn't exist (" + indexDirLoaded + "). Using Default:" + fEnv.getIndexDirectory());
            }
        }

        // workingDir
        String workingDirLoaded = Utils.getLineParam("workingDir", prefsText);
        if (! workingDirLoaded.equals("")) {
            File testworkingDir = new File(workingDirLoaded);
            if (testworkingDir.exists()) {
                resetWorkingDir(workingDirLoaded);
            } else {
                logger.info("loadPrefs() index dir doesn't exist (" + workingDirLoaded + "). Using Default:" + fEnv.getWorkingDirectory());
            }
        }
    }


    /**
     * Save Settings 
     *
     * TODO save this with Properties mechanism!
     */
    private void saveSettings() {
        // saves look and feel settings as well as browser preference
        // in file : savePrefsFiNa
        StringBuffer prefBuf = new StringBuffer();
        int numAdm = numGetAdminEmails();

        // gateway
        prefBuf.append("gateway=").append(gateway).append('\n');
        // gatewayPWD
        prefBuf.append("gatewayPwd=").append(gatewayPwd).append('\n');
        // max file size to index
        prefBuf.append("maxFileSizeToIndex=").append(getMaxFileSize()).append('\n');
        // maxNumHitsShown
        prefBuf.append("maxNumHitsShown=").append(maxNumHitsShown).append('\n');
        // gatewayUser
        prefBuf.append("gatewayUser=").append(gatewayUser).append('\n');
        // emailFormat
        prefBuf.append("emailFormat=").append(emailFormat).append('\n');
        // loadExternal
        if (loadExternal) {
            prefBuf.append("loadExternal=true\n");
        } else {
            prefBuf.append("loadExternal=false\n");
        }
        // sendEmailNotice
        prefBuf.append("sendEmailNotice=").append(sendEmailNotice).append('\n');
        // numAdminEmails
        prefBuf.append("numAdminEmails=").append(numAdm).append('\n');
        for (int i = 0; i < numAdm; i++) {
            String temAdEm = (String) adminEmails.get(i);
            prefBuf.append("email").append(i).append('=').append(temAdEm).append('\n');
        }
        // browser
        prefBuf.append("browser=").append(defaultHndlr).append('\n');
        // laf
        prefBuf.append("laf=").append(lafChosen).append('\n');
        // indexDir
        prefBuf.append("indexDir=").append(fEnv.getIndexDirectory()).append('\n');
        // tempDir
        prefBuf.append("tempDir=").append(tempDir).append('\n');
        // workingDir
        prefBuf.append("workingDir=").append(fEnv.getWorkingDirectory()).append('\n');

        // save settings
        FileUtils.saveFile(fEnv.getUserPreferencesFile(), prefBuf);
    }


    private void resetTempDir(String toSet) {
        tempDir = toSet;
        rtfTextFile = FileUtils.addFolder(tempDir, "temp_rtf_file_" + USER_NAME + ".txt");
        pdfTextFile = FileUtils.addFolder(tempDir, "temp_pdf_file_" + USER_NAME + ".txt");
        ooTextFile = FileUtils.addFolder(tempDir, "temp_oo_file_" + USER_NAME + ".xml");
        ooMetaTextFile = FileUtils.addFolder(tempDir, "temp_oo_meta_file_" + USER_NAME + ".xml");
        ooTextOnlyFile = FileUtils.addFolder(tempDir, "temp_oo_text_file_" + USER_NAME + ".txt");
    }


    private void resetWorkingDir(String toSet) {
        String workingDir = toSet;

        fEnv.setWorkingDirectory(workingDir);
        fEnv.resetIndexListFile();
        fEnv.resetBookmarkFile();
        fEnv.resetArchiveDirectory();

        defaultSaveFolder = FileUtils.addFolder(workingDir, "saved_searches");

        checkDefaults();
    }


    private void sendEmail(StringBuffer message) {
        int numEs = adminEmails.size();
        String compName = "";
        try {
            compName = InetAddress.getLocalHost().toString();
        } catch (Exception eR) {
            compName = "localhost";
        }
        String subj = DateTimeUtils.getToday() + " " + EML_SUBJ + " " + compName;
        String[] addrs = new String[numEs];
        for (int i = 0; i < numEs; i++)
            addrs[i] = getEmail(i);
        EmailThread emt = new EmailThread(addrs, getEmailProps(), FROM_ADDR, message.toString(), subj);
        // emt.start();
        try {
            emt.sendEmail();
        } catch (Exception e) {
            logger.fatal("sendEmail() failed", e);
            setStatus(ERROR + " " + e.toString());
        }
    }


    private Properties getEmailProps() {
        // 
        Properties retP = System.getProperties();
        retP.put("mail.smtp.host", gateway);
        retP.put("password", gatewayPwd);
        retP.put("username", gatewayUser);
        return retP;
    }


    public void addEmail(String toAdd) {
        adminEmails.add(toAdd);
    }


    public Object[] getEmails() {
        return adminEmails.toArray();
    }


    public void removeEmail(int toRem) {
        adminEmails.remove(toRem);
    }


    public String getEmail(int idx) {
        return (String) adminEmails.get(idx);
    }


    public void setEmail(int idx, String em) {
        adminEmails.set(idx, em);
    }


    private boolean isTextEmailFormat() {
        boolean returnBool = true;
        if (emailFormat.equals(Messages.getString("DocSearch.htmlFormat")))
            returnBool = false;
        return returnBool;
    }


    private boolean sendNoticeOnIdxingChanges() {
        boolean returnBool = true;
        if (sendEmailNotice.equals("false"))
            returnBool = false;
        return returnBool;
    }


    private int numGetAdminEmails() {
        return adminEmails.size();
    } // end for numGetAdminEmails


    private void sendEmail(String subj, StringBuffer message) {
        int numEs = adminEmails.size();
        String[] addrs = new String[numEs];
        for (int i = 0; i < numEs; i++)
            addrs[i] = getEmail(i);
        EmailThread emt = new EmailThread(addrs, getEmailProps(), FROM_ADDR, message.toString(), subj);
        // emt.start();
        try {
            emt.setTextFormat(isTextEmailFormat());
            emt.sendEmail();
        } catch (Exception e) {
            logger.fatal("sendEmail() failed", e);
            setStatus(ERROR + " " + e.toString());
        }
    }


    public ArrayList getCdArrayList() {
        ArrayList returnArry = new ArrayList();
        DocSearcherIndex di;
        int numIdxs = indexes.size();
        // boolean hasCdromIdxs=false;
        for (int i = 0; i < numIdxs; i++) {
            di = (DocSearcherIndex) indexes.get(i);
            if (di.isCdrom()) {
                // hasCdromIdxs=true;
                returnArry.add(di);
            }
        }
        return returnArry;
    }


    private void doSearchableCdWiz() {
        //
        String CREATE_IDX_FIRST = Messages.getString("DocSearch.createIdxFirst");
        String CREATE_CD_STEPS = Messages.getString("DocSearch.createIdxInfo");
        int numIdxs = indexes.size();
        if (numIdxs == 0) {
            showMessage(dsErr, CREATE_IDX_FIRST + "\n\n" + CREATE_CD_STEPS);
        }
        else {
            ArrayList indexesToSelectFrom = new ArrayList();
            boolean hasCdromIdxs = false;
            for (int i = 0; i < numIdxs; i++) {
                DocSearcherIndex di = (DocSearcherIndex) indexes.get(i);
                if (di.isCdrom()) {
                    hasCdromIdxs = true;
                    indexesToSelectFrom.add(di);
                }
            }

            if (! hasCdromIdxs) {
                showMessage(dsErr, CREATE_IDX_FIRST + "\n\n" + CREATE_CD_STEPS);
            }
            else {
                // set the defaults
                String cdRootDirName = FileUtils.addFolder(tempDir, "CD_ROOT_DS");
                String splashImageFileName = FileUtils.addFolder(fEnv.getStartDirectory(), FileEnvironment.FILENAME_SPLASH_IMAGE);
                String startPageFileName = FileUtils.addFolder(fEnv.getStartDirectory(), FileEnvironment.FILENAME_START_PAGE);
                String helpPageFileName = FileUtils.addFolder(fEnv.getStartDirectory(), FileEnvironment.FILENAME_HELP_PAGE);
                // boolean copyAllFiles=true;
                CdAssistantDialog cad = new CdAssistantDialog(this, Messages.getString("DocSearch.cdAssistant"), true);
                cad.init();
                cad.setFields(helpPageFileName, splashImageFileName, startPageFileName, cdRootDirName);
                cad.setVisible(true);
                if (cad.confirmed()) {
                    createCDStuff(cad.getCdRootDirName(), cad.getSplashImageFileName(), cad.getStartPageFileName(), cad.getHelpPageFileName(), cad.getCopyAllFiles(), cad.getCDIdxList());
                }
            } // end for we have CDROM indexes to work with
        } // end for we at least have some indexes
    }


    private String getCdsList(ArrayList idxs) {
        StringBuffer rb = new StringBuffer();
        if (idxs.size() > 0) {
            Iterator it = idxs.iterator();
            while (it.hasNext()) {
                DocSearcherIndex di = (DocSearcherIndex) it.next();
                rb.append(di.getDescription());
                rb.append('\n');
            }
        }
        return rb.toString();
    }


    /**
     * 
     * @param cdRootDirName
     * @param splashImageFileName
     * @param startPageFileName
     * @param helpPageFileName
     * @param copyAllFiles
     * @param indexesToSelectFrom
     */
    private void createCDStuff(String cdRootDirName,
            String splashImageFileName,
            String startPageFileName, 
            String helpPageFileName,
            boolean copyAllFiles,
            ArrayList indexesToSelectFrom) {
        if (logger.isInfoEnabled()) {
            logger.info("createCDStuff('"
                    + cdRootDirName + "', '"
                    + splashImageFileName + "', '"
                    + startPageFileName + "', '"
                    + helpPageFileName + "', '"
                    + copyAllFiles + "', '"
                    + indexesToSelectFrom + "') entered");
        }

        boolean madeStuff = true;
        StringBuffer errBuf = new StringBuffer();
        StringBuffer sB = new StringBuffer();

        sB.append("<html><head><title>DocSearcher Index List - CDROM</title></head><body>\n<table>");

        if (logger.isDebugEnabled()) {
            logger.debug("createCDStuff() check virtual cdrom root dir = '" + cdRootDirName + "'");
        }
        // CREATE THE CD ROOT DIR
        File cdrDirFi = new File(cdRootDirName);
        if (! cdrDirFi.exists()) {
            madeStuff = cdrDirFi.mkdir();
            if (! madeStuff) {
                errBuf.append('\n');
                errBuf.append(Messages.getString("DocSearch.unableToMkCDFold"));
            }
        }

        // COPY THE DOCSEARCH.JAR FILE
        if (madeStuff) {
            // TODO change some hard coded variables to constants!!!
            String newDocSearchFileName = FileUtils.addFolder(cdRootDirName, "DocSearch.jar");
            String oldDocSearchFileName = FileUtils.addFolder(fEnv.getStartDirectory(), "DocSearch.jar");
            String libsDir = FileUtils.addFolder(fEnv.getStartDirectory(), "lib");
            String newlibsFolder = FileUtils.addFolder(cdRootDirName, "lib");
            File testOldDS = new File(oldDocSearchFileName);
            if (testOldDS.exists()) {
                if (logger.isDebugEnabled()) {
                    logger.debug("createCDStuff() copy DocSearch.jar  ('" + oldDocSearchFileName + "')");
                }
                copyFile(oldDocSearchFileName, newDocSearchFileName);
            }
            else {
                logger.error("createCDStuff() can't find DocSearch.jar ('" + oldDocSearchFileName + "')");
                madeStuff = false;
                errBuf.append('\n');
                errBuf.append(Messages.getString("DocSearch.unableToFindDSjar"));
            }

            // create lib dir and copy all libs
            File newLibsDir = new File(newlibsFolder);
            madeStuff = newLibsDir.mkdir();
            if (madeStuff) {
                File libsFolder = new File(libsDir);
                String[] libs = libsFolder.list();
                // TODO why not copyFilessss???
                for (int z = 0; z < libs.length; z++) {
                    String curLibFileName = FileUtils.addFolder(libsDir, libs[z]);
                    String newLibFileName = FileUtils.addFolder(newlibsFolder, libs[z]);
                    if (logger.isDebugEnabled()) {
                        logger.debug("createCDStuff() copy lib '" + curLibFileName + "' to '" + newLibFileName + "'");
                    }
                    copyFile(curLibFileName, newLibFileName);
                }
            }
            else {
                logger.error("createCDStuff() can't create lib dir ('" + newlibsFolder + "')");
                errBuf.append('\n');
                errBuf.append(Messages.getString("DocSearch.failToCreateDir") + " : " + newlibsFolder);
            }
        }

        // COPY THE START AND HELP PAGES AS WELL AS THE SPLASH and ICONS -
        // IF THEY EXIST!
        if (madeStuff) {
            String newSpFiName = FileUtils.addFolder(cdRootDirName, FileEnvironment.FILENAME_START_PAGE);
            File testSp = new File(startPageFileName);
            if (testSp.exists()) {
                if (logger.isDebugEnabled()) {
                    logger.debug("createCDStuff() copy '" + startPageFileName + "' to '" + newSpFiName + "'");
                }
                copyFile(startPageFileName, newSpFiName);
            }
            String newHpFiName = FileUtils.addFolder(cdRootDirName, FileEnvironment.FILENAME_HELP_PAGE);
            File testHp = new File(helpPageFileName);
            if (testHp.exists()) {
                if (logger.isDebugEnabled()) {
                    logger.debug("createCDStuff() copy '" + helpPageFileName + "' to '" + newHpFiName + "'");
                }
                copyFile(helpPageFileName, newHpFiName);
            }
            String newSplashFiName = FileUtils.addFolder(cdRootDirName, FileEnvironment.FILENAME_SPLASH_IMAGE);
            File testSplashFi = new File(splashImageFileName);
            if (testSplashFi.exists()) {
                if (logger.isDebugEnabled()) {
                    logger.debug("createCDStuff() copy '" + splashImageFileName + "' to '" + newSplashFiName + "'");
                }
                copyFile(splashImageFileName, newSplashFiName);
            }
            // TODO change some hard coded variables to constants!!! (icons)
            String oldIconsDir = fEnv.getIconDirectory();
            String newIconsDir = FileUtils.addFolder(cdRootDirName, "icons");
            File testIcons = new File(newIconsDir);
            if (! testIcons.exists()) {
                madeStuff = testIcons.mkdir();
                if (madeStuff) {
                    if (logger.isDebugEnabled()) {
                        logger.debug("createCDStuff() copy icons from '" + oldIconsDir + "' to '" + newIconsDir + "'");
                    }
                    copyFiles(oldIconsDir, newIconsDir);
                }
                else {
                    logger.error("createCDStuff() can't create icon dir '" + testIcons + "'");
                    errBuf.append('\n');
                    errBuf.append(Messages.getString("DocSearch.failToCreateDir") + " : " + newIconsDir);
                }
            }
        }

        // NOW COPY OVER THE INDEX FILES
        if (madeStuff) {
            // TODO change some hard coded variables to constants!!!
            String cdIdxsTemp = FileUtils.addFolder(cdRootDirName, "cdrom_indexes");
            String actualItdxsDir = FileUtils.addFolder(cdIdxsTemp, "indexes");
            File testCDIDXSTemp = new File(cdIdxsTemp);
            if (! testCDIDXSTemp.exists()) {
                madeStuff = testCDIDXSTemp.mkdir();
                if (! madeStuff) {
                    logger.error("createCDStuff() can't create dir '" + testCDIDXSTemp + "'");
                    errBuf.append('\n');
                    errBuf.append(Messages.getString("DocSearch.failToCreateDir") + " : " + cdIdxsTemp);
                }
            }

            // create the sub dir for the indexes themsevels - ...indexes
            if (madeStuff) {
                File testActFi = new File(actualItdxsDir);
                if (! testActFi.exists()) {
                    madeStuff = testActFi.mkdir();
                    if (! madeStuff) {
                        logger.error("createCDStuff() can't create dir '" + testActFi + "'");
                        errBuf.append("\n");
                        errBuf.append(Messages.getString("DocSearch.failToCreateDir") + " : " + actualItdxsDir);
                    }
                }
            }

            // copy the indexes
            if (madeStuff) {
                Iterator it = indexesToSelectFrom.iterator();
                while (it.hasNext()) {
                    DocSearcherIndex di = (DocSearcherIndex) it.next();
                    String curOldIdxDir = di.getIndexPath();
                    String curOldPath = di.getPath();
                    String curPnameOnly = Utils.getNameOnly(curOldPath);
                    String curNameOnly = Utils.getNameOnly(curOldIdxDir);
                    curOldIdxDir = FileUtils.addFolder(fEnv.getIndexDirectory(), curNameOnly);
                    String curNewIdxDir = FileUtils.addFolder(actualItdxsDir, curNameOnly);
                    String curNewPath = FileUtils.addFolder(cdRootDirName, curPnameOnly);

                    // create index dir
                    File newIdxFi = new File(curNewIdxDir);
                    madeStuff = newIdxFi.mkdir();
                    if (! madeStuff) {
                        logger.error("createCDStuff() can't create index dir '" + newIdxFi + "'");
                        errBuf.append("\n");
                        errBuf.append(Messages.getString("DocSearch.failToCreateDir") + " : " + curNewIdxDir);
                    }
                    else {
                        logger.info("createCDStuff() start copying index files from '" + curOldIdxDir + "' to '" + curNewIdxDir + "'");
                        copyFiles(curOldIdxDir, curNewIdxDir);

                        // build our save buffer
                        sB.append("\n<tr>");
                        sB.append("\n<td>");
                        sB.append(di.getDescription());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getPath());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        if (di.getShouldBeSearched()) {
                            sB.append('0');
                        }
                        else {
                            sB.append('1');
                        }
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getDepth());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getIndexPath());
                        sB.append("</td>");
                        // now the isWeb stuff and date
                        sB.append("\n<td>");
                        if (di.getIsWeb()) {
                            sB.append("true");
                        } else {
                            sB.append("false");
                        }
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getMatch());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getReplace());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getLastIndexed());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getIndexPolicy());
                        sB.append("</td>");
                        sB.append("\n<td>");
                        sB.append(di.getArchiveDir());
                        sB.append("</td>");
                        sB.append("</tr>\n");

                        // copy all files
                        if (copyAllFiles) {
                            // copy from di.path to CD Root
                            File testNewCFi = new File(curNewPath);
                            if (! testNewCFi.exists()) {
                                if (testNewCFi.mkdir()) {
                                    copyFiles(curOldPath, curNewPath);
                                }
                                else {
                                    logger.error("createCDStuff() can't create dir '" + testNewCFi + "'");
                                }
                            }
                        }

                        logger.info("createCDStuff() finished copying index files from '" + curOldIdxDir + "' to '" + curNewIdxDir + "'");
                    }
                }

                sB.append("\n</table></body></html>");

                // save cdrom index list
                FileUtils.saveFile(FileUtils.addFolder(cdIdxsTemp, "cdrom_indexes_list.htm"), sB);
            }
        }

        // check cd creating was successfully
        if (madeStuff) {
            showMessage(Messages.getString("DocSearch.readyForBurning"), Messages.getString("DocSearch.cdMadeSuccess") + " \n\t  " + cdRootDirName);            
        }
        else {
            showMessage(Messages.getString("DocSearch.errCrtgCDStuff"), errBuf.toString());
        }
    }


    private boolean isSearching() {
        return currentlySearching;
    }


    private void doThreadedSearch() {
        if ((searchField.getSelectedItem() != null) && (!isSearching())) {
            String searchText = searchField.getSelectedItem().toString().trim();
            if ((!searchText.equals("")) && (!searchText.equals(lastSearchedText))) {
                setStatus(plsWait + " " + dsSchin);
                ThreadedSearch ts = new ThreadedSearch(this, searchText);
                SwingUtilities.invokeLater(ts);
                // doSearch(searchText);
                lastSearchedText = searchText;
            } // end for has text
            // else setStatus(PROVIDE_TEXT);
        } // end for not null
    } // end for doThreadedSearch


    private void doNewSpiderIdx() {
        // this is the method where spidered indexes are made
        SpiderDialog sd = new SpiderDialog(this, CREATE_NEW_SPIDER_IDX, true);
        sd.init();
        sd.setVisible(true);
        if (sd.getConfirmed()) {
            String spiderUrl = sd.getUrlFieldText().trim();
            String desc = sd.getDesc();
            int maxDocsToGet = sd.getMax();
            try {
                createSpiderIdx(spiderUrl, maxDocsToGet, desc);
            }
            catch (Exception e) {
                logger.fatal("doNewSpiderIdx() failed", e);
                setStatus(e.toString());
            }
        }
    }


    public String getDownloadFileName(String contT, String urlS) {
        String retS = "temp_spidered_document_" + USER_NAME;
        if (contT.toLowerCase().endsWith("html"))
            retS += ".htm";
        else {
            if (urlS.endsWith(".pdf"))
                retS += ".pdf";
            if (urlS.endsWith(".doc"))
                retS += ".doc";
            if (urlS.endsWith(".xls"))
                retS += ".xls";
            if (urlS.endsWith(".sxw"))
                retS += ".sxw";
            if (urlS.endsWith(".sxc"))
                retS += ".sxc";
            if (urlS.endsWith(".txt"))
                retS += ".txt";
            if (urlS.endsWith(".htm"))
                retS += ".htm";
            if (urlS.endsWith(".html"))
                retS += ".htm";
            if (urlS.endsWith(".shtml"))
                retS += ".htm";
            if (urlS.endsWith(".do"))
                retS += ".htm";
            if (urlS.endsWith("/"))
                retS += ".htm";
            if (urlS.endsWith(".jsp"))
                retS += ".htm";
            if (urlS.endsWith(".asp"))
                retS += ".htm";
            if (urlS.endsWith(".cfm"))
                retS += ".htm";
            if (urlS.endsWith(".cfml"))
                retS += ".htm";
            if (urlS.endsWith(".aspx"))
                retS += ".htm";
        }
        return retS;
    }


    private void createSpiderIdx(String spiderUrl, int maxDocsToGet, String desc) throws IOException {
        String outFile = FileUtils.addFolder(tempDir, "tmp_spider_links_" + USER_NAME + ".txt");
        String noUnd = Utils.replaceAll(" ", desc, "_");
        String idxFoldr = FileUtils.addFolder(fEnv.getIndexDirectory(), noUnd);
        /* Setup the index object */
        File idxpthfi = new File(idxFoldr);
        idxpthfi.mkdir();
        DocSearcherIndex dsi = new DocSearcherIndex(spiderUrl, desc, true, maxDocsToGet, idxFoldr, true, outFile, spiderUrl, DateTimeUtils.getToday(), 0, fEnv.getArchiveDirectory());
        IndexWriter writer = new IndexWriter(idxFoldr, new StandardAnalyzer(), true);
        // writer.setUseCompoundFile(true);
        LinkFinder lf = new LinkFinder(spiderUrl, outFile, maxDocsToGet, this, dsi, writer);
        lf.init();
        lf.getAllLinks();
        writer.close(); // close the writer
        indexes.add(dsi);
    } // end for createSpiderIdx


    public long getMaxFileSize() {
        return maxFileSizeInt;
    }


    public void setMaxFileSize(long toGet) {
        maxFileSizeInt = toGet;
    }


    public String getCurStatus() {
        return curStatusString;
    }


    public String getDefaultHndlr() {
        return defaultHndlr;
    }


    public String getErrorText() {
        return dsErr;
    }


    public int getMaxNumHitsShown() {
        return maxNumHitsShown;
    }


    public boolean getLoadExternal() {
        return loadExternal;
    }


    public Iterator getIndexIterator() {
        return indexes.iterator();
    }


    public boolean indexesEmpty() {
        return indexes.isEmpty();
    }


    public int numIndexes() {
        return indexes.size();
    }


    public DocSearcherIndex getDSIndex(int toGet) {
        return (DocSearcherIndex) indexes.get(toGet);
    }


    public boolean getIsWorking() {
        return isWorking;
    }


    public void setIsWorking(boolean toSet) {
        isWorking = toSet;
        iconButtons[11].setEnabled(isWorking);
    }


    public void doStop() {
        setIsWorking(false);
    }


    public void setProgressMax(long toSet) {
        pPanel.setMaxPos(toSet);
    }


    public void setCurProgress(long toSet) {
        pPanel.setCurPos(toSet);
    }


    public void setCurProgressMSG(String toSet) {
        pPanel.setMSG(toSet);
    }


    public void resetProgress() {
        pPanel.reset();
    }


    public String getLafChosen() {
        return lafChosen;
    }


    /**
     * Method listAllProperties
     */
    private void listAllProps() {
        // Get all system properties
        // user.country = US, user.language = en
        String userCountry = System.getProperty("user.country");
        String userLanguage = System.getProperty("user.language");
        String localityType = userLanguage + '_' + userCountry;
        logger.log(NoticeLevel.NOTICE, "listAllProps() using language: " + localityType);

        if (! localityType.toLowerCase().equals("en_us")) {
            logger.log(NoticeLevel.NOTICE, "ListAllProps() To create a translation for your language; translate the file docSearch.properties and save it as docSearch_" + localityType + ".properties");
        }
    }
}
