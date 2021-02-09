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
package org.jab.docsearch.converters;

import org.apache.log4j.Logger;
import org.apache.poi.hssf.eventusermodel.HSSFListener;
import org.apache.poi.hssf.record.BOFRecord;
import org.apache.poi.hssf.record.BoundSheetRecord;
import org.apache.poi.hssf.record.LabelSSTRecord;
import org.apache.poi.hssf.record.NumberRecord;
import org.apache.poi.hssf.record.Record;
import org.apache.poi.hssf.record.RowRecord;
import org.apache.poi.hssf.record.SSTRecord;

/**
 * This class allows POI excel text extraction to function with string buffers.
 *
 * @version $Id: ExcelListener.java,v 1.4 2005/10/08 15:52:08 henschel Exp $
 */
public class ExcelListener implements HSSFListener {
    /**
     * Log4J logger
     */
    private Logger logger = Logger.getLogger(getClass().getName());
    private StringBuffer excelText = new StringBuffer();
    private SSTRecord sstrec;


    /**
     * This method listens for incoming records and handles them as required.
     * 
     * @param record  The record that was found while reading.
     */
    public void processRecord(Record record) {
        try {
            switch (record.getSid()) {
                case BOFRecord.sid: {
                    BOFRecord bof = (BOFRecord) record;
                    if (bof.getType() == BOFRecord.TYPE_WORKBOOK) {
                        logger.debug("processRecords() encountered workbook");
                    }
                    else if (bof.getType() == BOFRecord.TYPE_WORKSHEET) {
                        break;
                    }
                }
                case BoundSheetRecord.sid: {
                    // BoundSheetRecord bsr = (BoundSheetRecord)record;

                    break;
                }
                case RowRecord.sid: {
                    // RowRecord rowrec = (RowRecord)record;

                    break;
                }
                case NumberRecord.sid: {
                    NumberRecord numrec = (NumberRecord) record;
                    
                    excelText.append(numrec.getValue());
                    excelText.append('\n');

                    break;
                }
                // SSTRecords store a array of unique strings used in Excel
                case SSTRecord.sid: {
                    sstrec = (SSTRecord) record;

                    for (int k = 0; k < sstrec.getNumUniqueStrings(); k++) {
                        excelText.append(sstrec.getString(k));
                        excelText.append('\n');
                    }

                    break;
                }
                case LabelSSTRecord.sid: {
                    LabelSSTRecord lrec = (LabelSSTRecord) record;

                    excelText.append(sstrec.getString(lrec.getSSTIndex()));
                    excelText.append('\n');

                    break;
                }
            }
        }
        catch (Exception e) {
            logger.error("processRecords() failed for Excel file", e);
        }
    }


    /**
     * Get text of the Excel document
     *
     * @return text of the Excel document 
     */
    public StringBuffer getText() {
        return excelText;
    }
}
