import hex from 'hex-string';

const parseMemo = (memoHex: string): string | null => {
  if (!memoHex || memoHex.length < 2) return null;

  // First, check if this is a memo (first byte is less than 'f6' (246))
  if (parseInt(memoHex.substr(0, 2), 16) >= 246) return null;

  // Else, parse as Hex string
  const textDecoder = new TextDecoder();
  const memo = textDecoder.decode(hex.decode(memoHex));
  if (memo === '') return null;

  return memo;
};

export default parseMemo;
