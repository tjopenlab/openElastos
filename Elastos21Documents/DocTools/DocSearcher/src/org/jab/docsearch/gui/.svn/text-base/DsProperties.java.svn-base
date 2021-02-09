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
package org.jab.docsearch.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;

import org.jab.docsearch.DocSearch;
import org.jab.docsearch.FileEnvironment;
import org.jab.docsearch.utils.Messages;
import org.jab.docsearch.utils.docTypeHandler;

/**
 * Class DsProperties
 * 
 * @version $Id: DsProperties.java,v 1.5 2005/10/25 19:56:12 henschel Exp $
 */
public final class DsProperties extends JDialog implements ActionListener {
    /**
     * FileEnvironment
     */
    private final static FileEnvironment fEnv = FileEnvironment.getInstance();
    private DocSearch monitor;
    private int numPanels = 2;
    public static final String CANCEL = Messages.getString("DocSearch.btnCancel");
    public static final String OK = Messages.getString("DocSearch.ok");
    private static final String APPLY = Messages.getString("DocSearch.btnApply");
    private static final String BROWSE = Messages.getString("DocSearch.btnBrowse");
    private static final String SELECT = Messages.getString("DocSearch.btnSelect");
    private static final String PROVIDE_IDX_DIR = Messages.getString("DocSearch.provIdxDir");
    private static final String ADD = Messages.getString("DocSearch.btnAdd");
    private static final String REMOVE = Messages.getString("DocSearch.lblRemove");
    private static final String NEW_HANDLER = Messages.getString("DocSearch.newHandler");
    private static final String EDIT_HANDLER = Messages.getString("DocSearch.editHandler");
    private static final String EDIT = Messages.getString("DocSearch.btnEdit");
    private static final String DS_DIR = Messages.getString("DocSearch.dsIdxDir");
    private static final String DS_DIR_TAB = Messages.getString("DocSearch.lblIdxDir");
    private static final String DS_DIR_EXP = Messages.getString("DocSearch.dsIdxDirExp");
    private static final String COPY_DIR_FILES = Messages.getString("DocSearch.copyDirFiles");
    private static final String SELECT_DS_DIR = Messages.getString("DocSearch.selectDsIdxDir");
    private static final String TEMP_DIR = Messages.getString("DocSearch.tempDir");
    private static final String TEMP_DIR_EXP = Messages.getString("DocSearch.tempDirExp");
    private static final String SELECT_TEMP_DIR = Messages.getString("DocSearch.selectTempDir");
    private static final String SELECT_WORKING_DIR = Messages.getString("DocSearch.selectWorkingDir");
    private static final String WORKING_DIR_LABEL = Messages.getString("DocSearch.workingDirLbl");
    private static final String WORKING_DIR_EXP = Messages.getString("DocSearch.workingDirExp");
    private static final String WORKING_DIR_TITLE = Messages.getString("DocSearch.workingDirTitle");
    private static final String LOAD_WEB_PAGES_EXTERNALLY = Messages.getString("DocSearch.loadExternal");
    // email config
    private JPanel completeEmailPanel = new JPanel();
    private JPanel emailPanel = new JPanel();
    private String EMAIL_ADDRESS = Messages.getString("DocSearch.emailAddress");
    private String EMAIL_ADDRESSES = Messages.getString("DocSearch.emailAddresses");
    private String EMAIL_SETTINGS = Messages.getString("DocSearch.emailSettings");
    private String SEND_EMAIL_NOTICE_NOTE = Messages.getString("DocSearch.sendEmail");
    private String SEND_EMAIL_NOTICE = Messages.getString("DocSearch.sendMail");
    private String GATEWAY_USER = Messages.getString("DocSearch.gateWayUser");
    private String NOTIFICATIONS = Messages.getString("DocSearch.notifications");
    private String EMAIL_GATEWAY = Messages.getString("DocSearch.emailGateway");
    private String GATEWAY_PWD = Messages.getString("DocSearch.gatewayPwd");
    private String REMOVE_EMAIL = Messages.getString("DocSearch.removeEmail");
    private String EDIT_EMAIL = Messages.getString("DocSearch.editEmail");
    private String ADD_EMAIL = Messages.getString("DocSearch.addEmail");
    private String EMAIL_FORMAT = Messages.getString("DocSearch.emailFormat");
    public String TEXT_FORMAT = Messages.getString("DocSearch.textFormat");
    public String HTML_FORMAT = Messages.getString("DocSearch.htmlFormat");
    private String MAX_FILE_SIZE = Messages.getString("DocSearch.maxFsToIdx");
    //
    private JLabel maxFiSizeLbl = new JLabel(MAX_FILE_SIZE);
    private JTextField maxSizeField = new JTextField(10);
    private JPanel maxFileSizePanel = new JPanel();
    //
    private String MAX_HITS_LABEL = Messages.getString("DocSearch.maxHitsLbl");
    private String MAX_HITS_TITLE = Messages.getString("DocSearch.maxHitsTit");
    private JLabel maxHitLbl = new JLabel(MAX_HITS_LABEL);
    private JTextField maxField = new JTextField(5);
    private JPanel maxPanel = new JPanel();
    private JPanel maxAllPanel = new JPanel();
    //
    private String[] emailAddresses = { "", "" };
    private JList emailList = new JList(emailAddresses);
    private JScrollPane emailPane = new JScrollPane(emailList);
    private JPanel emailButtonsPanel = new JPanel();
    private JButton editButton = new JButton(EDIT);
    private JButton addButton = new JButton(ADD);
    private JButton removeButton = new JButton(REMOVE);
    //
    private JPanel gatewayPanel = new JPanel();
    private JPanel noticePanel = new JPanel();
    private JCheckBox sendEmailBx = new JCheckBox(SEND_EMAIL_NOTICE);
    private JLabel sendEmailLbl = new JLabel(SEND_EMAIL_NOTICE_NOTE);
    //
    private ButtonGroup bg = new ButtonGroup();
    private JRadioButton textRB = new JRadioButton(TEXT_FORMAT);
    private JRadioButton htmlRB = new JRadioButton(HTML_FORMAT);
    //
    private JPanel gatewyp = new JPanel();
    private JLabel gateWayLbl = new JLabel(EMAIL_GATEWAY);
    private JTextField gateWayField = new JTextField(12);
    private JPanel gatewayUserPanel = new JPanel();
    private JLabel gatewayUserLbl = new JLabel(GATEWAY_USER);
    private JTextField gatewayUserField = new JTextField(12);
    private JPanel gatewayPwdPanel = new JPanel();
    private JLabel gatewayPwdLbl = new JLabel(GATEWAY_PWD);
    private JPasswordField gatewayPwdField = new JPasswordField(12);
    //
    private String[] handlerItems = { "", "" };
    private JList handlerList = new JList(handlerItems);
    //
    private JPanel workingDirPanel = new JPanel();
    private JPanel workingPanel = new JPanel();
    private JLabel workingDirLbl = new JLabel(WORKING_DIR_LABEL);
    private JLabel workingDirExpLbl = new JLabel(WORKING_DIR_EXP);
    private JTextField workingDirField = new JTextField(12);
    private JButton workingDirButton = new JButton(SELECT_WORKING_DIR);
    //
    private JPanel tempDirPanel = new JPanel();
    private JPanel tempFoldPanel = new JPanel();
    private JLabel tempDirExpLbl = new JLabel(TEMP_DIR_EXP);
    private JLabel tempDirLbl = new JLabel(TEMP_DIR);
    private JTextField tempDirField = new JTextField(12);
    private JButton tempDirButton = new JButton(SELECT_TEMP_DIR);
    //
    private JLabel defaultHndlrLbl = new JLabel(Messages.getString("DocSearch.lblDfltHndlr"));
    private JTextField defaultHndlrField = new JTextField(12);
    private JButton browseButton = new JButton(BROWSE);
    //
    private JPanel dsDirPanel = new JPanel();
    private JLabel dsDirLabel = new JLabel(DS_DIR_EXP);
    private JLabel dsDirFieldLabel = new JLabel(DS_DIR);
    private JButton dsSelDirButton = new JButton(SELECT_DS_DIR);
    private JCheckBox copyDirFiles = new JCheckBox(COPY_DIR_FILES);
    private JTextField dsDirField = new JTextField(12);
    //
    private JCheckBox loadExternal = new JCheckBox(LOAD_WEB_PAGES_EXTERNALLY);
    //
    private JButton okButton = new JButton(APPLY);
    private JButton cancelButton = new JButton(CANCEL);
    //
    private JButton addEmailButton = new JButton(ADD_EMAIL);
    private JButton removeEmailButton = new JButton(REMOVE_EMAIL);
    private JButton editEmailButton = new JButton(EDIT_EMAIL);
    //
    private JPanel allDirsPanel = new JPanel();
    //
    private JPanel bp = new JPanel();
    private JPanel leftSideListPanel = new JPanel();
    private JScrollPane listPane = new JScrollPane(handlerList);
    private JPanel rightButPanel = new JPanel();
    private JPanel rbp = new JPanel();
    private JPanel[] panels;
    private JTabbedPane tp = new JTabbedPane();
    //
    private boolean confirmed = false;
    private int returnInt = -1;
    private String lafChosen = "";
    //
    private JPanel uiPanel = new JPanel();
    private String[] uiList = { "" };
    private JComboBox uiChoice = new JComboBox(uiList);
    private JLabel uiLabel = new JLabel(Messages.getString("DocSearch.uiChoice"));


    public DsProperties(DocSearch monitor, String title, boolean modal) {
        super(monitor, title, modal);
        this.monitor = monitor;
        listPane.setPreferredSize(new Dimension(350, 200));
        // set up the buttons
        okButton.addActionListener(this);
        cancelButton.addActionListener(this);
        browseButton.addActionListener(this);
        removeButton.addActionListener(this);
        editButton.addActionListener(this);
        addButton.addActionListener(this);
        sendEmailBx.addActionListener(new CbListener());
        removeEmailButton.addActionListener(this);
        editEmailButton.addActionListener(this);
        addEmailButton.addActionListener(this);
        //
        dsSelDirButton.addActionListener(this);
        tempDirButton.addActionListener(this);
        workingDirButton.addActionListener(this);
        //
        workingDirPanel.add(workingDirLbl);
        workingDirPanel.add(workingDirField);
        workingDirPanel.add(workingDirButton);
        //
        workingPanel.setLayout(new BorderLayout());
        workingPanel.setBorder(new TitledBorder(WORKING_DIR_TITLE));
        workingPanel.add(workingDirExpLbl, BorderLayout.NORTH);
        workingPanel.add(workingDirPanel, BorderLayout.CENTER);
        //
        maxPanel.add(maxHitLbl);
        maxPanel.add(maxField);
        //
        maxAllPanel.setLayout(new BorderLayout());
        // maxAllPanel.setBorder(new TitledBorder(MAX_HITS_TITLE));
        maxAllPanel.add(maxPanel, BorderLayout.CENTER);
        //
        tempFoldPanel.add(tempDirLbl);
        tempFoldPanel.add(tempDirField);
        tempFoldPanel.add(tempDirButton);
        //
        tempDirPanel.setLayout(new BorderLayout());
        tempDirPanel.setBorder(new TitledBorder(TEMP_DIR));
        tempDirPanel.add(tempDirExpLbl, BorderLayout.NORTH);
        tempDirPanel.add(tempFoldPanel, BorderLayout.CENTER);
        //
        JPanel uiP = new JPanel();
        uiP.add(uiLabel);
        uiP.add(uiChoice);
        //
        maxFileSizePanel.add(maxFiSizeLbl);
        maxFileSizePanel.add(maxSizeField);
        JPanel mfsW = new JPanel();
        mfsW.add(maxFileSizePanel);
        //
        JPanel comMaxP = new JPanel();
        comMaxP.setLayout(new BorderLayout());
        comMaxP.add(mfsW, BorderLayout.NORTH);
        comMaxP.add(maxAllPanel, BorderLayout.CENTER);
        JPanel cmpW = new JPanel();
        cmpW.add(comMaxP);
        //
        uiPanel.setLayout(new BorderLayout());
        uiPanel.add(uiP, BorderLayout.NORTH);
        uiPanel.add(cmpW, BorderLayout.CENTER);
        uiPanel.add(loadExternal, BorderLayout.SOUTH);
        JPanel uiWrap = new JPanel();
        uiWrap.add(uiPanel);
        //
        bg.add(textRB);
        bg.add(htmlRB);
        //
        leftSideListPanel.add(listPane);
        //
        bp.add(okButton);
        bp.add(cancelButton);
        //
        JPanel dirFieldPanel = new JPanel();
        dirFieldPanel.add(dsDirFieldLabel);
        dirFieldPanel.add(dsDirField);
        dirFieldPanel.add(dsSelDirButton);
        //
        dsDirPanel.setLayout(new BorderLayout());
        dsDirPanel.setBorder(new TitledBorder(DS_DIR));
        dsDirPanel.add(dsDirLabel, BorderLayout.NORTH);
        dsDirPanel.add(dirFieldPanel, BorderLayout.CENTER);
        dsDirPanel.add(copyDirFiles, BorderLayout.SOUTH);
        //
        allDirsPanel.setLayout(new BorderLayout());
        allDirsPanel.add(tempDirPanel, BorderLayout.NORTH);
        allDirsPanel.add(dsDirPanel, BorderLayout.CENTER);
        allDirsPanel.add(workingPanel, BorderLayout.SOUTH);
        //
        JPanel dp = new JPanel();
        dp.add(allDirsPanel);
        //
        rightButPanel.setLayout(new BorderLayout());
        rightButPanel.add(addButton, BorderLayout.NORTH);
        rightButPanel.add(removeButton, BorderLayout.CENTER);
        rightButPanel.add(editButton, BorderLayout.SOUTH);
        rbp.add(rightButPanel);
        // load up the GUI
        //
        okButton.setMnemonic(KeyEvent.VK_A);
        okButton.setToolTipText(APPLY);
        //
        //
        cancelButton.setMnemonic(KeyEvent.VK_C);
        cancelButton.setToolTipText(CANCEL);
        //
        browseButton.setMnemonic(KeyEvent.VK_B);
        browseButton.setToolTipText(BROWSE);
        //
        JPanel hndlerPanel = new JPanel();
        JPanel lowerHP = new JPanel();
        JPanel upperHP = new JPanel();
        upperHP.setLayout(new BorderLayout());
        upperHP.setBorder(new TitledBorder(Messages.getString("DocSearch.hndlrTitle")));
        upperHP.add(leftSideListPanel, BorderLayout.WEST);
        upperHP.add(rbp, BorderLayout.EAST);
        lowerHP.add(defaultHndlrLbl);
        lowerHP.add(defaultHndlrField);
        lowerHP.add(browseButton);
        //
        hndlerPanel.setLayout(new BorderLayout());
        hndlerPanel.add(upperHP, BorderLayout.CENTER);
        hndlerPanel.add(lowerHP, BorderLayout.SOUTH);
        //
        //
        emailButtonsPanel.setLayout(new BorderLayout());
        emailButtonsPanel.add(addEmailButton, BorderLayout.NORTH);
        emailButtonsPanel.add(removeEmailButton, BorderLayout.CENTER);
        emailButtonsPanel.add(editEmailButton, BorderLayout.SOUTH);
        JPanel emailCPpanel = new JPanel();
        emailCPpanel.add(emailButtonsPanel);
        //
        gatewayPwdPanel.add(gatewayPwdLbl);
        gatewayPwdPanel.add(gatewayPwdField);
        //
        gatewyp.add(gateWayLbl);
        gatewyp.add(gateWayField);
        //
        gatewayUserPanel.add(gatewayUserLbl);
        gatewayUserPanel.add(gatewayUserField);
        //
        gatewayPanel.setLayout(new BorderLayout());
        gatewayPanel.setBorder(new TitledBorder(EMAIL_GATEWAY));
        gatewayPanel.add(gatewyp, BorderLayout.NORTH);
        gatewayPanel.add(gatewayUserPanel, BorderLayout.CENTER);
        gatewayPanel.add(gatewayPwdPanel, BorderLayout.SOUTH);
        //
        //
        JPanel formatPanel = new JPanel();
        formatPanel.setLayout(new BorderLayout());
        formatPanel.setBorder(new TitledBorder(EMAIL_FORMAT));
        formatPanel.add(textRB, BorderLayout.NORTH);
        formatPanel.add(htmlRB, BorderLayout.CENTER);
        //
        JPanel combinedFormatGatewayPanel = new JPanel();
        combinedFormatGatewayPanel.setLayout(new BorderLayout());
        combinedFormatGatewayPanel.add(gatewayPanel, BorderLayout.CENTER);
        combinedFormatGatewayPanel.add(formatPanel, BorderLayout.EAST);
        //
        noticePanel.setLayout(new BorderLayout());
        noticePanel.setBorder(new TitledBorder(EMAIL_SETTINGS));
        noticePanel.add(sendEmailLbl, BorderLayout.NORTH);
        noticePanel.add(sendEmailBx, BorderLayout.CENTER);
        //
        emailPanel.setLayout(new BorderLayout());
        emailPanel.setBorder(new TitledBorder(EMAIL_ADDRESSES));
        emailPanel.add(emailPane, BorderLayout.CENTER);
        emailPanel.add(emailCPpanel, BorderLayout.EAST);
        //
        completeEmailPanel.setLayout(new BorderLayout());
        completeEmailPanel.add(noticePanel, BorderLayout.NORTH);
        completeEmailPanel.add(emailPanel, BorderLayout.CENTER);
        completeEmailPanel.add(combinedFormatGatewayPanel, BorderLayout.SOUTH);

        tp.addTab(Messages.getString("DocSearch.hndlersTab"), null, hndlerPanel, Messages.getString("DocSearch.hndlersTabInf"));
        tp.addTab(Messages.getString("DocSearch.guiStuff"), null, uiWrap, Messages.getString("DocSearch.guiStuffInf"));
        tp.addTab(DS_DIR_TAB, null, dp, DS_DIR_EXP);
        tp.addTab(NOTIFICATIONS, null, completeEmailPanel, NOTIFICATIONS);
        //
        panels = new JPanel[numPanels];
        for (int i = 0; i < numPanels; i++)
            panels[i] = new JPanel();
        panels[0].add(tp);
        //
        panels[numPanels - 1].add(bp);
        //
        // NOW PLACE THE GUI ONTO A GRIDBAG
        // put in the gridbag stuff
        getContentPane().setLayout(new GridLayout(1, numPanels));
        GridBagLayout gridbaglayout = new GridBagLayout();
        GridBagConstraints gridbagconstraints = new GridBagConstraints();
        getContentPane().setLayout(gridbaglayout);
        //
        for (int i = 0; i < numPanels; i++) {
            gridbagconstraints.fill = 1;
            gridbagconstraints.insets = new Insets(1, 1, 1, 1);
            gridbagconstraints.gridx = 0;
            gridbagconstraints.gridy = i;
            gridbagconstraints.gridwidth = 1;
            gridbagconstraints.gridheight = 1;
            gridbagconstraints.weightx = 0.0D;
            gridbagconstraints.weighty = 0.0D;
            gridbaglayout.setConstraints(panels[i], gridbagconstraints);
            getContentPane().add(panels[i]);
        }

    }


    public void init() {
        //
        setLafs();
        setList();
        defaultHndlrField.setText(monitor.getDefaultHndlr());
        dsDirField.setText(fEnv.getIndexDirectory());
        tempDirField.setText(monitor.tempDir);
        workingDirField.setText(fEnv.getWorkingDirectory());
        if (monitor.emailFormat.equals(TEXT_FORMAT))
            textRB.setSelected(true);
        else if (monitor.emailFormat.equals(HTML_FORMAT))
            htmlRB.setSelected(true);
        else
            textRB.setSelected(true);
        maxField.setText("" + monitor.getMaxNumHitsShown());
        //
        Object[] emls = monitor.getEmails();
        if (emls != null)
            emailList.setListData(emls);
        gateWayField.setText(monitor.gateway);
        gatewayPwdField.setText(monitor.gatewayPwd);
        gatewayUserField.setText(monitor.gatewayUser);
        if (monitor.sendEmailNotice.equals("true"))
            sendEmailBx.setSelected(true);
        cb();
        //
        pack();
        // center this dialog
        Rectangle frameSize = getBounds();
        Dimension screenD = Toolkit.getDefaultToolkit().getScreenSize();
        int screenWidth = screenD.width;
        int screenHeight = screenD.height;
        int newX = 0;
        int newY = 0;
        if (screenWidth > frameSize.width)
            newX = (screenWidth - frameSize.width) / 2;
        if (screenHeight > frameSize.height)
            newY = (screenHeight - frameSize.height) / 2;
        if ((newX != 0) || (newY != 0))
            setLocation(newX, newY);
        if (monitor.getLoadExternal())
            loadExternal.setSelected(true);
        else
            loadExternal.setSelected(false);
        long mfs = (monitor.getMaxFileSize() / 1024);
        maxSizeField.setText("" + mfs);
    }


    public void actionPerformed(ActionEvent actionevent) {
        String s = actionevent.getActionCommand();
        if (s.equals(APPLY)) {
            returnInt = tp.getSelectedIndex();
            String newIndexDir = dsDirField.getText().trim();
            if ((returnInt == 2) && (newIndexDir.equals("")))
                monitor.showMessage(DocSearch.dsErr, PROVIDE_IDX_DIR);
            else {
                confirmed = true;
                this.setVisible(false);
            }
        }
        // end for ok
        else if (s.equals(ADD)) {
            NewHandlerDialog nhd = new NewHandlerDialog(monitor, NEW_HANDLER, true);
            nhd.init();
            nhd.setVisible(true);
            if (nhd.returnBool) {
                //
                docTypeHandler dh = new docTypeHandler(nhd.extField.getText(), nhd.descField.getText(), nhd.appField.getText());
                monitor.handlerList.add(dh);
                setList();
            }
        } // end for adding a handler
        else if (s.equals(REMOVE)) {
            int chosen = handlerList.getSelectedIndex();
            if (chosen != -1) {
                removeItemAt(chosen);
                monitor.handlerList.remove(chosen);
                setList();
            }
        } // end for adding a handler
        else if (s.equals(EDIT)) {
            int chosen = handlerList.getSelectedIndex();
            if (chosen != -1) {
                //
                NewHandlerDialog nhd = new NewHandlerDialog(monitor, EDIT_HANDLER, true);
                // set the values of the selected item
                nhd.init();
                nhd.setDTH((docTypeHandler) monitor.handlerList.get(chosen));
                nhd.setVisible(true);
                if (nhd.returnBool) {
                    docTypeHandler dh = (docTypeHandler) monitor.handlerList.get(chosen);
                    dh = new docTypeHandler(nhd.extField.getText(), nhd.descField.getText(), nhd.appField.getText());
                    monitor.handlerList.set(chosen, dh);
                    setList();
                }
            } // end for item chosen
        } // end for editing a handler
        else if (s.equals(BROWSE)) {
            JFileChooser fdo = new JFileChooser();
            fdo.setCurrentDirectory(new File(fEnv.getUserHome()));
            fdo.setFileSelectionMode(JFileChooser.FILES_ONLY);
            int fileGotten = fdo.showDialog(this, SELECT);
            if (fileGotten == JFileChooser.APPROVE_OPTION) {
                File file = fdo.getSelectedFile();
                String fNa = file.toString();
                defaultHndlrField.setText(fNa);
            }
        }
        // 
        else if (s.equals(SELECT_WORKING_DIR)) {
            JFileChooser fdo = new JFileChooser();
            fdo.setCurrentDirectory(new File(fEnv.getWorkingDirectory()));
            fdo.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            int fileGotten = fdo.showDialog(this, SELECT);
            if (fileGotten == JFileChooser.APPROVE_OPTION) {
                File file = fdo.getSelectedFile();
                String fNa = file.toString();
                workingDirField.setText(fNa);
            }
        } else if (s.equals(SELECT_TEMP_DIR)) {
            JFileChooser fdo = new JFileChooser();
            fdo.setCurrentDirectory(new File(fEnv.getUserHome()));
            fdo.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            int fileGotten = fdo.showDialog(this, SELECT);
            if (fileGotten == JFileChooser.APPROVE_OPTION) {
                File file = fdo.getSelectedFile();
                String fNa = file.toString();
                tempDirField.setText(fNa);
            }
        } else if (s.equals(CANCEL)) {
            confirmed = false;
            this.setVisible(false);
        } else if (s.equals(REMOVE_EMAIL)) {
            int itemNo = emailList.getSelectedIndex();
            if (itemNo != -1)
                removeEmailItem(itemNo);
        } else if (s.equals(ADD_EMAIL)) {
            DsEmail me = new DsEmail(this, ADD + " " + EMAIL_ADDRESS, true);
            me.init();
            me.setVisible(true);
            if (me.confirmed) {
                //
                String em = me.nameField.getText();
                if (!em.equals(""))
                    addEmail(em);
            } // end for me
        } else if (s.equals(EDIT_EMAIL)) {
            int itemNo = emailList.getSelectedIndex();
            if (itemNo != -1) {
                DsEmail me = new DsEmail(this, EDIT + " " + EMAIL_ADDRESS, true);
                me.init();
                me.nameField.setText(monitor.getEmail(itemNo));
                me.setVisible(true);
                if (me.confirmed) {
                    String newEm = me.nameField.getText();
                    if (!newEm.equals(""))
                        replaceEmail(itemNo, newEm);
                }
            }
        } else if (s.equals(SELECT_DS_DIR)) {
            JFileChooser fdo = new JFileChooser();
            fdo.setCurrentDirectory(new File(fEnv.getIndexDirectory()));
            fdo.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            int fileGotten = fdo.showDialog(this, SELECT);
            if (fileGotten == JFileChooser.APPROVE_OPTION) {
                File file = fdo.getSelectedFile();
                String fNa = file.toString();
                dsDirField.setText(fNa);
            }
        }
    }


    public void setList() {
        int numHndlrs = monitor.handlerList.size();
        if (numHndlrs > 0) {
            String listItems[] = new String[numHndlrs];
            Iterator it = monitor.handlerList.iterator();
            docTypeHandler dh;
            int curI = 0;
            while (it.hasNext()) {
                dh = (docTypeHandler) it.next();
                listItems[curI] = dh.descName();
                curI++;
            }
            handlerList.setListData(listItems);
        }
    } // end for setlist


    public void removeItemAt(int removeItemNum) {
        if (removeItemNum != -1) {
            int newNum = handlerList.getModel().getSize() - 1;
            // System.out.println("Item to skip:
            // "+(String)AllPages.getModel().getElementAt(removeItemNum));
            if (newNum == 0)
                handlerList.removeAll();
            else if (newNum > 0) {
                String[] nData = new String[newNum];
                int curAd = 0;
                for (int i = 0; i < newNum + 1; i++) {
                    if (i != removeItemNum) {
                        nData[curAd] = (String) handlerList.getModel().getElementAt(i);
                        curAd++;
                    }
                } // end for adding
                handlerList.setListData(nData);
            } // end if more than one item
        } // end if not zero
    } // end for removeItemAt


    public void setLafs() {
        int matchInt = 0;
        boolean foundMtch = false;
        ArrayList lafs = monitor.getLafs();
        if (!lafs.isEmpty()) {
            // int numLafs=lafs.size();
            Iterator it = lafs.iterator();
            String laf;
            int curLF = 1;
            while (it.hasNext()) {
                laf = (String) it.next();
                if (!monitor.lafChosen.equals("")) {
                    if (laf.toLowerCase().equals(monitor.getLafChosen().toLowerCase())) {
                        matchInt = curLF;
                        foundMtch = true;
                    }
                }
                uiChoice.addItem(laf);
                curLF++;
            }
        }
        if (foundMtch)
            uiChoice.setSelectedIndex(matchInt);
    } // end for setlafs


    public void cb() {
        if (!sendEmailBx.isSelected()) {
            addEmailButton.setEnabled(false);
            removeEmailButton.setEnabled(false);
            editEmailButton.setEnabled(false);
            gatewayUserField.setEnabled(false);
            gatewayPwdField.setEnabled(false);
            gateWayField.setEnabled(false);
            emailList.setEnabled(false);
            textRB.setEnabled(false);
            htmlRB.setEnabled(false);
        } else {
            addEmailButton.setEnabled(true);
            removeEmailButton.setEnabled(true);
            editEmailButton.setEnabled(true);
            gatewayUserField.setEnabled(true);
            gatewayPwdField.setEnabled(true);
            gateWayField.setEnabled(true);
            emailList.setEnabled(true);
            textRB.setEnabled(true);
            htmlRB.setEnabled(true);
        }
    }

    class CbListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            // String CMD=e.getActionCommand();
            cb();
        } // end of action
    } // end for radio listener


    public void addEmail(String toAdd) {
        // adds email to our list
        monitor.addEmail(toAdd);
        emailList.setListData(monitor.getEmails());
    } // end for addEmail


    public void replaceEmail(int idx, String toRep) {
        monitor.setEmail(idx, toRep);
        emailList.setListData(monitor.getEmails());
    }


    public void removeEmailItem(int toRem) {
        monitor.removeEmail(toRem);
        emailList.setListData(monitor.getEmails());
    }


    public String getGateWayFieldText() {
        return gateWayField.getText();
    }


    public String gatewayPwdFieldText() {
        return new String(gatewayPwdField.getPassword());
    }


    public String gatewayUserFieldText() {
        return gatewayUserField.getText();
    }


    public String getTmpFieldText() {
        return tempDirField.getText();
    }


    public String getDsDirFieldText() {
        return dsDirField.getText();
    }


    public String workingDirFieldText() {
        return workingDirField.getText();
    }


    public String maxSizeField() {
        return maxSizeField.getText();
    }


    public String maxFieldText() {
        return maxField.getText();
    }


    public String defltHndlrText() {
        return defaultHndlrField.getText();
    }


    public String lafSelected() {
        return (String) uiChoice.getModel().getSelectedItem();
    }


    public boolean sendEmailBxSelected() {
        return sendEmailBx.isSelected();
    }


    public boolean textRBSelected() {
        return textRB.isSelected();
    }


    public boolean copyDirFilesSelected() {
        return copyDirFiles.isSelected();
    }


    public boolean loadExternalSelected() {
        return loadExternal.isSelected();
    }


    public int getReturnInt() {
        return returnInt;
    }


    public boolean getConfirmed() {
        return confirmed;
    }
} // end for class
