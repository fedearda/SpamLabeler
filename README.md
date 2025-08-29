# Spam Labeler

This project is a spam email detection system that classifies emails as **spam** or **not spam** using a **decision tree** model based on various email features. These features include sender reputation, suspicious words, exclamation marks, attachment type, and more.

## Features
- **Email Sender**: Evaluates whether the email is from a trusted contact.
- **Exclamation Marks**: Counts the number of exclamation marks in the email subject and body.
- **Suspicious Words**: Looks for keywords commonly associated with spam (e.g., "free", "urgent", "win").
- **Reputation Score**: Uses a sender's reputation score to influence the classification.
- **Attachment**: Evaluates whether an attachment is present, which can sometimes indicate spam.
- **Capital Letters Percentage**: Analyzes the percentage of capital letters in the email body.

## Technologies Used

- **C++**: Core language for implementing the spam classifier.
- **Decision Tree Algorithm**: Used to classify emails as spam or not based on feature thresholds.
- **File I/O**: Reads input data from various text files and processes it into structured data.

## Files

### 1. **contactList.txt**
This file contains a list of trusted contacts. Emails from these contacts are considered more likely to be **not spam**.

### 2. **emails.tsv**
This file contains email data, with each email's sender, subject, attachment type, and body.

Example:
```markdown
alice@example.com "Win a free iPhone" "none" "Click here to claim your prize now!"
bob@example.com "Meeting Schedule" "agenda.docx" "Let's meet at 3pm to discuss the roadmap."
spammy@scam.com "Urgent: Account Suspended" "none" "Login now to reactivate your account."

### 3. **reputationList.txt**
This file stores the reputation scores of different senders. A higher reputation score means the email is less likely to be spam.

Example:
```markdown
alice@example.com,4.3
bob@example.com,7.9
spammy@scam.com,1.12


### 4. **suspiciousWords.txt**
This file contains a list of words commonly found in spam emails (e.g., "free", "win", "urgent"). The presence of these words in the subject or body can increase the likelihood of an email being spam.

Example:
```markdown
free
urgent
win
dollars
rich


## Features Extraction

The system extracts the following features for each email:

1. **Is from an untrusted contact**: Whether the sender is listed in the trusted contacts.
2. **Number of exclamatory marks**: Counts the number of `!` symbols in the subject and body of the email.
3. **Percentage of capital letters**: Percentage of uppercase letters in the body.
4. **Contains suspicious words**: Whether the email contains any words from the `suspiciousWords.txt`.
5. **Has an attachment**: Whether the email has any attachment or not.
6. **Reputation score of the sender**: The reputation score associated with the sender from the `reputationList.txt`.

These features are then passed to a **decision tree** for classification.

## Decision Tree

A decision tree is manually built to classify emails into spam or not spam based on thresholds for each feature.

**Thresholds for features**:
- **Untrusted contact**: Threshold is 0.5
- **Exclamation marks**: Threshold is 3.5
- **Capital letters**: Threshold is 15%
- **Suspicious words**: Threshold is 0.5
- **Has attachment**: Threshold is 0.5
- **Reputation score**: Threshold is 8.0

The decision tree is structured with nodes that correspond to the features and their respective thresholds.

## Usage

1. Clone the repository:

```bash
git clone https://github.com/yourusername/spam-labeler.git
cd spam-labeler
